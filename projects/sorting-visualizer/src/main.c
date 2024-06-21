#include "raylib.h"
#include "sorting.h"
#include <pthread.h>

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
