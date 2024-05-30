
#include <functional/colors.h>
#include <engine/classic_tetris_game_screen.h>

#include <raylib/raylib.h>

int main() {

    ScreenSize screenSize {1000, 850, 1.0};
    InitWindow (screenSize.m_width, screenSize.m_height, "Raylib Tetris");
    SetTargetFPS (60);

    ClassicTetrisGameScreen aGameScreen (screenSize);
    aGameScreen.Init();

    while (!WindowShouldClose()) {
        BeginDrawing();
        aGameScreen.Tick();
        ClearBackground (Colors::darkGrey);

        EndDrawing();
    }
    CloseWindow();
}