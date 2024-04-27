#include <raylib/raylib.h>

int main () {

    InitWindow (300, 600, "Raylib Tetris");

    SetTargetFPS (60);

    while (!WindowShouldClose()) {
        BeginDrawing ();
        ClearBackground (DARKGRAY);

        EndDrawing();
    }

    CloseWindow ();
}