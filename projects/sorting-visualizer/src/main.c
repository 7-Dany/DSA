#include "raylib.h"
#include "sorting.h"
#include <pthread.h>
#include <stdlib.h>

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

void* sort(void *sort_args)
{
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
        default: break;// No way I'm allowing bogo sort.
    }

    return NULL;
}

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight= 500;

    const int array_size = 50;
    int *array = (int*)malloc(array_size * sizeof(int));
    const int bar_width = screenWidth / array_size;

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

        switch (GetKeyPressed()) {
            case KEY_S:
                args.type = SHUFFLE;
                pthread_create(&thread, NULL, sort, (void*)&args);
                break;
            case KEY_B:
                args.delay = 10;
                args.type = BUBBLE;
                pthread_create(&thread, NULL, sort, (void*)&args);
                break;
            case KEY_R:
                args.type = RADIX;
                pthread_create(&thread, NULL, sort, (void*)&args);
                break;
            case KEY_M:
                args.type = MERGE;
                pthread_create(&thread, NULL, sort, (void*)&args);
                break;
        }

        ClearBackground(GetColor(0x181818FF));

        BeginDrawing();
        {
            for (int i = 0; i < array_size; i++) {
                Color color = ColorFromHSV(array[i], 1, 1);
                DrawRectangle(i * bar_width, screenHeight - array[i], bar_width, array[i], color);
            } 
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
