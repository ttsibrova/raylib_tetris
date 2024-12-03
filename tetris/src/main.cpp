
#include <graphics/colors.h>
#include <engine/screen_manager.h>

#include <raylib/raylib.h>
#include <engine/audio_manager.h>

#include <engine/settings_reader.h>

int main() {
    Image icon = LoadImage ("resources/tetris_a.png");

    Settings::Init();
    Settings& mainSettings = Settings::GetInstance();


    ScreenSize screenSize {1280, 900, mainSettings.GetScale()};

    std::string name = "Raylib Tetris by Lur4N1k";
    if (mainSettings.GetScale() < 0.6f) {
        name = "Tetris: Magnifying glass is not included";
    }
    if (mainSettings.GetScale() > 1.f) {
        name = "Tetris: Bigger doesn't mean better";
    }

    InitWindow (screenSize.m_width * screenSize.m_scale, screenSize.m_height * screenSize.m_scale, name.c_str());
    SetWindowIcon (icon);

    AudioManager::GetInstance().Init (mainSettings.IsAudioEnabled());

    SetTargetFPS (60);
    SetExitKey (KEY_NULL);

    ScreenManager manager (screenSize);

    while (!WindowShouldClose() && !manager.ShouldClose()) {
        BeginDrawing();
        //ClearBackground (Colors::darkGrey);

        manager.Update();
        EndDrawing();
    }
    CloseWindow();
    UnloadImage (icon);
}