#include "raylib.h"
#include "sorting.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef enum {
    INSERTION = 0,
    BUBBLE,
    BOGO,
    SELECTION,
    MERGE,
    QUICK, 
    RADIX, 
    SHUFFLE,
    SORT_COUNT,
} Sorting_Algs;

typedef struct {
    int *arr;
    int len;
    Sorting_Algs type;
    uint32_t delay;
} Sort_Args;

typedef struct {
    Vector2 min;
    Vector2 max;
    Color color;
    void (*func)(void);
} Button;

Button button_create(Vector2 pos, int width, int height) 
{
    Button btn = {0};
    btn.min = pos;
    btn.max.x = btn.min.x + width;
    btn.max.y = btn.min.y + height;

    return btn;
}

void button_update(Button *btn)
{
    Vector2 mouse = GetMousePosition();
    if (mouse.x >= btn->min.x && mouse.x <= btn->max.x) {
        if (mouse.y >= btn->min.y && mouse.y <= btn->max.y) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                btn->func();
            }
        }
    }
}

bool thread_running = false;

void* sort(void *sort_args)
{
    thread_running = true;

    Sort_Args args = *(Sort_Args*)sort_args;
    int *array = args.arr;
    int len = args.len;
    uint32_t delay = args.delay;
    Sorting_Algs type = args.type;

    switch (type) {
        case INSERTION: insertion_sort(array, len, delay); break;
        case BUBBLE: bubble_sort(array, len, delay); break;
        case SELECTION: selection_sort(array, len, delay); break;
        case MERGE: merge_sort(array, len, delay); break;
        case QUICK: quick_sort(array, len, delay); break;
        case RADIX: radix_sort(array, len, delay); break;
        case SHUFFLE: shuffle_array(array, len, delay); break;
        // case BOGO: bogo_sort(array, len, delay);
        default: break;
    }

    thread_running = false;

    return NULL;
}

#define create_thread(args)                               \
  do {                                                    \
    pthread_t thread;                                     \
    pthread_create(&thread, NULL, sort, (void*)&(args));  \
    pthread_detach(thread);                               \
  } while (0)

int main(void)
{
    const int screenWidth = 1600;
    const int screenHeight = 900;

    const int array_size = 100;
    const Vector2 frame_start = {
        .x = 0,
        .y = 0,
    };
    const Vector2 frame_end = {
        .x = screenWidth - 100,
        .y = screenHeight,
    };
    const int frame_width = frame_end.x - frame_start.x;
    const int frame_height = frame_end.y - frame_start.y;
    const int bar_width = frame_width / array_size;
    const float factor = (frame_height - 50.f) / (array_size * 10);

    bool show_wheel = false;

    int *array = (int*)malloc(array_size * sizeof(int));

    for (int i = 0; i < array_size; i++) {
        array[i] = (i + 1) * 10;
    }

    InitWindow(screenWidth, screenHeight, "Sorting Visualizer");

    Sort_Args args = {
        .arr = array,
        .len = array_size,
        .delay = 50,
        .type = BUBBLE,
    };

    while (! WindowShouldClose()) {
        if (! thread_running) {
            switch (GetKeyPressed()) {
                case KEY_S:
                    args.type = SHUFFLE;
                    args.delay = 1;
                    create_thread(args);
                    break;
                case KEY_B:
                    args.delay = 1;
                    args.type = BUBBLE;
                    create_thread(args);
                    break;
                case KEY_R:
                    args.delay = 30;
                    args.type = RADIX;
                    create_thread(args);
                    break;
                case KEY_M:
                    args.delay = 30;
                    args.type = MERGE;
                    create_thread(args);
                    break;
                case KEY_I:
                    args.delay = 10;
                    args.type = INSERTION;
                    create_thread(args);
                    break;
                case KEY_C:
                    args.delay = 30;
                    args.type = SELECTION;
                    create_thread(args);
                    break;
                case KEY_Q:
                    args.delay = 30;
                    args.type = QUICK;
                    create_thread(args);
                    break;
            }
        }

        if (IsKeyDown(KEY_TAB)) 
            show_wheel = true;
        else 
            show_wheel = false;

        ClearBackground(GetColor(0x181818FF));

        BeginDrawing();
        {
            for (int i = 0; i < array_size; i++) {
                float hue = (array[i] / (array_size * 10.f)) * 360;
                Color color = ColorFromHSV(hue, 1, 1);
                float height = array[i] * factor;
                Vector2 pos = {.x = (i * bar_width) + frame_start.x, .y = screenHeight - height};
                Vector2 size = {.x = bar_width, .y = height};
                DrawRectangleV(pos, size, color);
            } 

            if (show_wheel) {
                DrawRectangle(0, 0, screenWidth, screenHeight, ColorAlpha(BLACK, 0.4f));
                Vector2 center = {.x = screenWidth / 2.f, .y = screenHeight / 2.f};
                DrawCircleLinesV(center, 250, WHITE);
                DrawCircleLinesV(center, 150, WHITE);
                Vector2 points[8][4];
                Vector2 endpos; 
                Vector2 startpos;
                Vector2 prevstart;
                Vector2 prevend;
                int j = 0;
                for (int i = 0; i <= SORT_COUNT; i++) {
                    float angle = (i * (360.f / SORT_COUNT)) * PI / 180.f; 
                    float prev_angle =  ((i - 1) * (360.f / SORT_COUNT)) * PI / 180.f;
                    prevstart.x = (cosf(prev_angle) * 150) + center.x;
                    prevstart.y = (sinf(prev_angle) * 150) + center.y;
                    prevend.x = (cosf(prev_angle) * 100) + prevstart.x;
                    prevend.y = (sinf(prev_angle) * 100) + prevstart.y;
                    startpos.x = (cosf(angle) * 150) + center.x;
                    startpos.y = (sinf(angle) * 150) + center.y;
                    endpos.x = (cosf(angle) * 100) + startpos.x;
                    endpos.y = (sinf(angle) * 100) + startpos.y;
                    DrawLineEx(startpos, endpos, 2.f, WHITE);
                    if (i > 0) {
                        points[i-1][0] = prevstart;
                        points[i-1][1] = prevend;
                        points[i-1][2] = startpos;
                        points[i-1][3] = endpos;
                    }
                }
                if (CheckCollisionPointPoly(GetMousePosition(), points[0], 4)) {
                    DrawCircleV(GetMousePosition(), 10, RED);
                }

            }
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
