#include "raylib.h"
#include <pthread.h>

void insertionSort(int *array, int len) {
    for (int i = 1; i < len; i++) {
        int temp = array[i];
        int j = i - 1;

        while (j >= 0 && array[j] > temp) {
            array[j + 1] = array[j];
            j--;
        }

        array[j + 1] = temp;
    }
}

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight= 500;

    InitWindow(screenWidth, screenHeight, "Sorting Visualizer");

    while (! WindowShouldClose()) {


        ClearBackground(GetColor(0x181818FF));
        BeginDrawing();
        {

        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}