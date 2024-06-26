#include "raylib.h"
#include "raymath.h"
#include "sorting.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
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

const char* get_sort_name(Sorting_Algs alg)
{
    switch (alg) {
        case INSERTION: return "insertion";
        case BUBBLE   : return "bubble";
        case BOGO     : return "bogo";
        case SELECTION: return "selection";
        case MERGE    : return "merge";
        case QUICK    : return "quick";
        case RADIX    : return "radix";
        case SHUFFLE  : return "shuffle";
        case SORT_COUNT: return "sort_count";
        default: return NULL;
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
        case BUBBLE   : bubble_sort(array, len, delay); break;
        case SELECTION: selection_sort(array, len, delay); break;
        case MERGE    : merge_sort(array, len, delay); break;
        case QUICK    : quick_sort(array, len, delay); break;
        case RADIX    : radix_sort(array, len, delay); break;
        case SHUFFLE  : shuffle_array(array, len, delay); break;
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

#define in_range(i, l, h) ((i) >= (l) && (i) <= (h) ? true : false)

Sorting_Algs current_alg = SHUFFLE;

uint32_t get_delay(Sorting_Algs alg)
{
    switch (alg) {
        case INSERTION: return 10;
        case BUBBLE   : return 1;
        case BOGO     : return 0;
        case SELECTION: return 30;
        case MERGE    : return 30;
        case QUICK    : return 30;
        case RADIX    : return 30;
        case SHUFFLE  : return 1;
        default: return 0;
    }
}

#define screenWidth 1600
#define screenHeight 900

int get_sector()
{
    const float inc_angle = 360.f / SORT_COUNT;
    const Vector2 center = {.x = screenWidth / 2.f, .y = screenHeight / 2.f};
    Vector2 mousepos = GetMousePosition();
    float angle = Vector2LineAngle(center, mousepos) * RAD2DEG;
    if (angle < 0) angle += 360.f;
    float distance = Vector2Distance(center, mousepos);
    int sector = -1;
    
    if (in_range(distance, 150, 250)) {
        for (int i = 0; i < SORT_COUNT; i++) {
            if (in_range(angle, (inc_angle * i) + 1, (inc_angle * (i + 1)) - 1)) {
                sector = i;
                break;
            }
        }
    }

    return sector;
}

int main(void)
{
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
    int sector = -1;

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
                case KEY_SPACE:
                    args.type = current_alg;
                    args.delay = get_delay(current_alg);
                    create_thread(args);
                    break;
            }
        }

        if (IsKeyDown(KEY_TAB)) 
            show_wheel = true;
        else 
            show_wheel = false;

        if (show_wheel) {
            sector = get_sector();

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && sector != -1) {
                current_alg = sector;
            }
        }

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

            DrawText("algorithm:", frame_width + 5, 30, 20, WHITE);
            DrawText(get_sort_name(current_alg), frame_width + 5, 60, 20, YELLOW);

            if (show_wheel) {
                DrawRectangle(0, 0, screenWidth, screenHeight, ColorAlpha(BLACK, 0.4f));
                Vector2 center = {.x = screenWidth / 2.f, .y = screenHeight / 2.f};
                DrawCircleLinesV(center, 250, WHITE);
                DrawCircleLinesV(center, 150, WHITE);
                Vector2 endpos; 
                Vector2 startpos;
                const float inc_angle = 360.f / SORT_COUNT;
                for (int i = 0; i < SORT_COUNT; i++) {
                    float angle = (i * inc_angle) * DEG2RAD; 
                    startpos.x = (cosf(angle) * 150) + center.x;
                    startpos.y = (sinf(angle) * 150) + center.y;
                    endpos.x = (cosf(angle) * 100) + startpos.x;
                    endpos.y = (sinf(angle) * 100) + startpos.y;
                    DrawLineEx(startpos, endpos, 2.f, WHITE);
                }


                float start_angle = inc_angle / -2.f;
                for (int i = 0; i < SORT_COUNT; i++) {
                    float angle = (start_angle - (i * inc_angle)) * DEG2RAD;
                    startpos.x = (cosf(angle) * 200) + center.x;
                    startpos.y = (sinf(angle) * 200) + center.y;
                    Font font = GetFontDefault();
                    float space = 2.f;
                    float font_size = 20;
                    Color color = sector == i ? GREEN : WHITE;
                    const char *text = get_sort_name(i);
                    Vector2 size = MeasureTextEx(font, text, font_size, space);
                    DrawTextPro(font, text, startpos, (Vector2){.x = size.x / 2.f, .y = size.y / 2.f}, 
                                0.f, font_size, space, color);
                }
            
                // char temp[25];
                // sprintf(temp, "%d", sector);
                // sprintf(temp, "%f", angle);
                // DrawText(temp, mousepos.x, mousepos.y - 20, 20, RED);
            }
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
