#include "raylib.h"
#include "list.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <synchapi.h>

#define WIDTH 800
#define HEIGHT 500
#define maze_width 25
#define maze_height 25

typedef struct {
    int x;
    int y;
} int2;

typedef struct {
    bool u, d, l, r;
    bool v;
} Cell;

#define INLINE __attribute__((always_inline)) static inline

INLINE void init_2d(int *arr[], int rows, int cols, int val)
{
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            arr[r][c] = val;
        }
    }
}

INLINE void** alloc_2d(size_t element_size, size_t rows, size_t cols)
{
    void **arr = malloc(rows * sizeof(void*));
    
    for (size_t i = 0; i < rows; i++) {
        *(arr + i) = malloc(cols * element_size);
    }

    return arr;
}

#define in_range(x, y) (x >= 0 && x < maze_width && y >= 0 && y < maze_height)

INLINE int cell_neighbors(int2 *arr, Cell **maze, int2 cell)
{
    int2 left = {cell.x - 1, cell.y};
    int2 right = {cell.x + 1, cell.y};
    int2 top = {cell.x, cell.y - 1};
    int2 bottom = {cell.x, cell.y + 1};
    int ptr = 0;

    if (in_range(left.x, left.y) && maze[left.y][left.x].v == false) arr[ptr++] = left;
    if (in_range(right.x, right.y) && maze[right.y][right.x].v == false) arr[ptr++] = right;
    if (in_range(top.x, top.y) && maze[top.y][top.x].v == false) arr[ptr++] = top;
    if (in_range(bottom.x, bottom.y) && maze[bottom.y][bottom.x].v == false) arr[ptr++] = bottom;

    return ptr;
}

INLINE int open_neighbors(int2 *arr, Cell **maze, int2 cell)
{
    int2 left = {cell.x - 1, cell.y};
    int2 right = {cell.x + 1, cell.y};
    int2 top = {cell.x, cell.y - 1};
    int2 bottom = {cell.x, cell.y + 1};
    int ptr = 0;

    if (in_range(left.x, left.y) && maze[left.y][left.x].v == false) {
        if (maze[cell.y][cell.x].l) arr[ptr++] = left;
    }
    if (in_range(right.x, right.y) && maze[right.y][right.x].v == false) {
        if (maze[cell.y][cell.x].r) arr[ptr++] = right;
    }
    if (in_range(top.x, top.y) && maze[top.y][top.x].v == false) {
        if (maze[cell.y][cell.x].u) arr[ptr++] = top;
    }
    if (in_range(bottom.x, bottom.y) && maze[bottom.y][bottom.x].v == false) {
        if (maze[cell.y][cell.x].d) arr[ptr++] = bottom;
    } 

    return ptr;
}

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
} Dir;

INLINE int get_dir(int2 cell1, int2 cell2)
{
    if (cell1.x < cell2.x) {
        return RIGHT;
    }
    else if (cell1.x > cell2.x) {
        return LEFT;
    }
    else if (cell1.y < cell2.y) {
        return DOWN;
    }
    else if (cell1.y > cell2.y) {
        return UP;
    }

    return 0;
}

INLINE void connect_cells(Cell **maze, int2 cell1, int2 cell2)
{
    switch (get_dir(cell1, cell2)) {
        case RIGHT:
            maze[cell1.y][cell1.x].r = true;
            maze[cell2.y][cell2.x].l = true;
            break;
        case LEFT:
            maze[cell1.y][cell1.x].l = true;
            maze[cell2.y][cell2.x].r = true;
            break;
        case DOWN:
            maze[cell1.y][cell1.x].d = true;
            maze[cell2.y][cell2.x].u = true;
            break;
        case UP:
            maze[cell1.y][cell1.x].u = true;
            maze[cell2.y][cell2.x].d = true;
            break;
    }
}

int2 CELL;
bool running;
bool running2;

void generate_maze(Cell **maze)
{
    /*
    create a stack for backtracking
    choose a cell index at random from the grid to be current cell
    set visited cells to 1

    while visited cells < total cells
        get unvisited neighbors using cell_neighbors
        if at least one neighbor
            choose random neighbor to be new cell
            knock down wall between it and current cell using connect_cells
            push current cell to stack
            set current cell to new cell
            add 1 to visited cells
        else
            pop from stack to current cell
    */

    for (int r = 0; r < maze_height; r++) {
        for (int c = 0; c < maze_width; c++) {
            maze[r][c] = (Cell){0};
        }
    }
    SetRandomSeed(time(0));

    int2 stack[maze_width * maze_height];
    int stack_ptr = 0;
    int2 cell = {.x = GetRandomValue(0, maze_width - 1), .y = 0};
    int2 end = {.x = GetRandomValue(0, maze_width - 1), .y = maze_height - 1};
    maze[cell.y][cell.x].u = true;
    maze[end.y][end.x].d = true;
    int visited = 1;
    int2 neighbors[4];
    CELL = cell;

    while (visited < maze_width * maze_height) {
        int n = cell_neighbors(neighbors, maze, cell); 
        if (n > 0) {
            int i = GetRandomValue(0, n - 1);
            int2 neighbor = neighbors[i];
            connect_cells(maze, cell, neighbor);
            maze[neighbor.y][neighbor.x].v = true;
            stack[stack_ptr++] = cell;
            cell = neighbor;
            CELL = cell;
            visited += 1;
            Sleep(40);
        }
        else {
            cell = stack[stack_ptr - 1];
            stack_ptr -= 1;
        }
    }
}

void* generate_maze_thread(void *maze) 
{
    running = true;
    generate_maze((Cell**)maze);
    running = false;

    return NULL;
}

int2 SOLVING;
List(int2) SOLVE_PATH;

void solve_maze(Cell **maze)
{
    int2 start;
    int2 end;

    for (int i = 0; i < maze_width; i++) {
        if (maze[0][i].u) {
            start = (int2){.x = i, .y = 0};
        }
        if (maze[maze_height - 1][i].d) {
            end = (int2){.x = i, .y = maze_height - 1};
        }
    }

    for (int r = 0; r < maze_height; r++) {
        for (int c = 0; c < maze_width; c++) {
            maze[r][c].v = false;
        }
    }

    List(int2) stack;
    list_alloc(&stack);
    list_push(&stack, start);
    int2 neighbors[4];

    while (stack.count > 0) {
        int2 current = list_pop(&stack);
        SOLVING = current;
        list_push(&SOLVE_PATH, current);

        if (current.x == end.x && current.y == end.y) break;

        int n = open_neighbors(neighbors, maze, current);

        if (n == 0) {
            list_clear(&SOLVE_PATH);
        }

        for (int i = 0; i < n; i++) {
            int2 neighbor = neighbors[i];
            maze[neighbor.y][neighbor.x].v = true;
            list_push(&stack, neighbor);
        }
        Sleep(30);
    }
}

void* solve_maze_thread(void *maze) 
{
    running2 = true;
    solve_maze((Cell**)maze);
    running2 = false;

    return NULL;
}

#define vec2(_x, _y) ((Vector2){.x = (_x), .y = (_y)})

INLINE void draw_rect_lines(Cell cell, float x, float y, float width, float height, float thick, Color color)
{
    if (!cell.u) DrawLineEx(vec2(x, y), vec2(x + width, y), thick, color);
    if (!cell.d) DrawLineEx(vec2(x, y + height), vec2(x + width, y + height), thick, color);
    if (!cell.l) DrawLineEx(vec2(x, y), vec2(x, y + height), thick, color);
    if (!cell.r) DrawLineEx(vec2(x + width, y), vec2(x + width, y + height), thick, color);
}

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "maze");

    int startx = 200;
    int starty = 50;
    int frame_width = 400;
    int frame_height = 400;
    float square_width = (float)frame_width / maze_width;
    float square_height= (float)frame_height / maze_height;
    float padding = 3;
    Cell **maze = (Cell**)alloc_2d(sizeof(Cell), maze_height, maze_width);
    list_alloc(&SOLVE_PATH);
    // generate_maze(maze);

    while (! WindowShouldClose()) {

        if (IsKeyPressed(KEY_R)) {
            pthread_t thead; 
            pthread_create(&thead, NULL, generate_maze_thread, maze);
            pthread_detach(thead);
        }
        if (IsKeyPressed(KEY_S)) {
            pthread_t thead; 
            pthread_create(&thead, NULL, solve_maze_thread, maze);
            pthread_detach(thead);
        }

        ClearBackground(GetColor(0x181818FF));

        BeginDrawing();
        {
            for (int r = 0; r < maze_height; r++) {
                for (int c = 0; c < maze_width; c++) {
                    float x = startx + (c * square_width);
                    float y = starty + (r * square_height);
                    draw_rect_lines(maze[r][c], x, y, square_width, square_height, 2, WHITE);
                }
            }
            if (running) {
                DrawRectangleV(vec2(startx + (CELL.x * square_width), starty + (CELL.y * square_height)), 
                               vec2(square_width, square_height), ColorAlpha(GREEN, 0.6));
            }
            if (running2) {
                DrawRectangleV(vec2(startx + (SOLVING.x * square_width), starty + (SOLVING.y * square_height)), 
                                vec2(square_width, square_height), ColorAlpha(YELLOW, 0.6));
            }
            for (int i = 0; i < SOLVE_PATH.count; i++) {
                DrawRectangleV(vec2(startx + (SOLVE_PATH.items[i].x * square_width), starty + (SOLVE_PATH.items[i].y * square_height)), 
                                vec2(square_width, square_height), ColorAlpha(RED, 0.6));
            }
        }
        EndDrawing();
    }

    CloseWindow();
}
