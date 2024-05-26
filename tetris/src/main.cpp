
#include <engine/game.h>
#include <functional/colors.h>

#include <memory>

#include <raylib/raylib.h>

int main() {

    Game game;

    InitWindow (game.GetGameWidght(), game.GetGameHeight(), "Raylib Tetris");
    SetTargetFPS (60);

    game.Init();

    while (!WindowShouldClose()) {
        if (!game.CanPlay()) {
            game.Init();
        }
        if (!game.CanPlay() && (IsKeyPressed (KEY_ENTER) || IsGamepadAvailable(0) && IsGamepadButtonPressed (0, GAMEPAD_BUTTON_MIDDLE_RIGHT))) {
            game.Start();
        }
        BeginDrawing();
        ClearBackground (Colors::darkGrey);
        if (game.CanPlay()) {
            game.HandleInput();
            game.UpdateFallingBlock();
        }
        game.Draw();
        if (!game.CanPlay()) {
            DrawText ("Press ENTER to play", game.GetGameWidght() * 0.18, game.GetGameHeight () / 2 - 20, 50, YELLOW);
            DrawText ("Controls", game.GetGameWidght () * 0.42, game.GetGameHeight() / 2 + 70, 35, Colors::cyan);
            DrawText ("Move right - arrrow RIGHT / d-pad RIGHT", game.GetGameWidght() * 0.25, 530, 20, Colors::cyan_shade);
            DrawText ("Move left  - arrrow LEFT  / d-pad LEFT", game.GetGameWidght() * 0.26, 560, 20, Colors::cyan_shade);
            DrawText ("Move down  - arrrow DOWN  / d-pad DOWN", game.GetGameWidght() * 0.26, 590, 20, Colors::cyan_shade);
            DrawText ("Instant drop  - arrrow UP  / d-pad UP", game.GetGameWidght() * 0.27, 620, 20, Colors::cyan_shade);
            DrawText ("Rotate block - key R  / gamepad A", game.GetGameWidght() * 0.29, 650, 20, Colors::cyan_shade);
            DrawText ("Hold block - key E  / gamepad LB", game.GetGameWidght() * 0.3, 680, 20, Colors::cyan_shade);
        }
        EndDrawing();
    }

    CloseWindow();
}