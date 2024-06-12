
#include <graphics/colors.h>
#include <engine/screen_manager.h>

#include <raylib/raylib.h>

int main() {

    ScreenSize screenSize {1000, 850, 1.};
    InitWindow (screenSize.m_width * screenSize.m_scale, screenSize.m_height * screenSize.m_scale, "Raylib Tetris");

    InitAudioDevice();
    SetTargetFPS (60);
    SetExitKey (KEY_NULL);

    ScreenManager manager (screenSize);

    while (!WindowShouldClose() && !manager.ShouldClose()) {
        BeginDrawing();
        //ClearBackground (Colors::darkGrey);

        manager.Tick();
        EndDrawing();
    }
    CloseAudioDevice();
    CloseWindow();
}