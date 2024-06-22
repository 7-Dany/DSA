#include "raylib.h"
#include "sorting.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef enum {
    INSERTION,
    BUBBLE,
    BOGO,
    SELECTION,
    MERGE,
    QUICK, 
    RADIX, 
    SHUFFLE,
} Sorting_Algs;

typedef struct {
    int *arr;
    int len;
    Sorting_Algs type;
    uint32_t delay;
} Sort_Args;

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
        default: break;// No way I'm allowing bogo sort.
    }

    thread_running = false;

    return NULL;
}

int main(void)
{
    const int screenWidth = 1600;
    const int screenHeight = 900;

    const int array_size = 100;
    int *array = (int*)malloc(array_size * sizeof(int));
    const int bar_width = screenWidth / array_size;
    float factor = (screenHeight - 50.f) / (array_size * 10);

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
        pthread_t thread;

        if (! thread_running) {
            switch (GetKeyPressed()) {
                case KEY_S:
                    args.type = SHUFFLE;
                    args.delay = 1;
                    pthread_create(&thread, NULL, sort, (void*)&args);
                    break;
                case KEY_B:
                    args.delay = 1;
                    args.type = BUBBLE;
                    pthread_create(&thread, NULL, sort, (void*)&args);
                    break;
                case KEY_R:
                    args.type = RADIX;
                    args.delay = 30;
                    pthread_create(&thread, NULL, sort, (void*)&args);
                    break;
                case KEY_M:
                    args.type = MERGE;
                    pthread_create(&thread, NULL, sort, (void*)&args);
                    break;
            }
        }

        ClearBackground(GetColor(0x181818FF));

        BeginDrawing();
        {
            for (int i = 0; i < array_size; i++) {
                Color color = ColorFromHSV(array[i], 1, 1);
                float height = array[i] * factor;
                Vector2 pos = {.x = i * bar_width, .y = screenHeight - height};
                Vector2 size = {.x = bar_width, .y = height};
                DrawRectangleV(pos, size, color);
            } 
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
