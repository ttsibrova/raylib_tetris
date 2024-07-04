#pragma once
#include <raylib/raylib.h>

#include <utility>

namespace settings {
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

class Settings
{
public:
    static Settings& GetInstance();
    static void Init();

    void SetKeyboardMappings (settings::KeyboardMappings&& kmap) { m_kmap = std::move (kmap); }
    void SetGamepadMappings (settings::GamepadMappings&& gmap) { m_gmap = std::move (gmap); }
    void SetScale (float scale) { m_scale = scale; }
    void SetIsAudioEnabled (bool bIsAudioEnabled) { m_bIsAudioEnabled = bIsAudioEnabled; }

    const settings::KeyboardMappings& GetKeyboardMappings() const { return m_kmap; }
    settings::KeyboardMappings& GetKeyboardMappings() { return m_kmap; }
    const settings::GamepadMappings& GetGamepadMappings() const { return m_gmap; }
    settings::GamepadMappings& GetGamepadMappings() { return m_gmap; }
    float GetScale() { return m_scale; }
    bool IsAudioEnabled() { return m_bIsAudioEnabled; }

    Settings (Settings const&) = delete;
    void operator= (Settings const&) = delete;

private:
    Settings():
        m_scale (1.f),
        m_bIsAudioEnabled (true)
    {}

private:
    float            m_scale;
    bool             m_bIsAudioEnabled;
    settings::GamepadMappings  m_gmap;
    settings::KeyboardMappings m_kmap;
};


