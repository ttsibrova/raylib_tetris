
#include <functional/colors.h>
#include <engine/classic_tetris_game_screen.h>

#include <raylib/raylib.h>

int main() {

    ScreenSize screenSize {1000, 850, 1.};
    InitWindow (screenSize.m_width * screenSize.m_scale, screenSize.m_height * screenSize.m_scale, "Raylib Tetris");

    InitAudioDevice();
    SetTargetFPS (60);

    ClassicTetrisGameScreen aGameScreen (screenSize);
    aGameScreen.Init();

    while (!WindowShouldClose()) {
        BeginDrawing();
        aGameScreen.Tick();
        ClearBackground (Colors::darkGrey);

        EndDrawing();
    }
    CloseAudioDevice();
    CloseWindow();
}