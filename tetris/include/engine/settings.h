#pragma once
#include <raylib/raylib.h>

namespace Settings {
struct GamepadMappings
{
    GamepadButton m_HoldButton     = GAMEPAD_BUTTON_LEFT_TRIGGER_1;
    GamepadButton m_RotateButton   = GAMEPAD_BUTTON_RIGHT_FACE_DOWN;
    GamepadButton m_HardDropButton = GAMEPAD_BUTTON_LEFT_FACE_UP;
};

struct KeyboardMappings {
    KeyboardKey m_HoldKey       = KEY_E;
    KeyboardKey m_RotateKey     = KEY_R;
    KeyboardKey m_HardDropKey   = KEY_UP;
    KeyboardKey m_MoveRightKey  = KEY_RIGHT;
    KeyboardKey m_MoveLeftKey   = KEY_LEFT;
    KeyboardKey m_MoveDown      = KEY_DOWN;
};
}
