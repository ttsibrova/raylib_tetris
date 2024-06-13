#pragma once
#include <engine/command.h>
#include <engine/game_object.h>
#include <raylib/raylib.h>
#include <vector>
#include <stack>
#include <memory>

enum class Device {
    NONE,
    KEYBOARD,
    GAMEPAD
};

enum class ActionType {
    HOLD,
    PRESS
};

struct InputAction
{
    GamepadButton             m_mappedGButton = GAMEPAD_BUTTON_UNKNOWN;
    KeyboardKey               m_mappedKButton = KEY_NULL;
    ActionType                m_type;
    std::unique_ptr <Command> m_command;
};

struct InputLayer {
public:
    void AddAction (GamepadButton button, KeyboardKey key, ActionType type, std::unique_ptr <Command>&& command)
    {
        m_layerActions.emplace_back (button, key, type, std::move (command));
    }

public:
    std::vector <InputAction> m_layerActions;
};

class InputHandler: public GameObject
{
public:
    InputHandler ():
        m_lastActiveDevice (Device::KEYBOARD),
        m_gamepadId (0)
    {}

    virtual void Tick() override;

    void PushInputLayer (InputLayer* newLayer);
    bool PopInputLayer();

    void PushObject (Object* obj);
    bool PopObject();

    Device GetActiveDevice() const { return m_lastActiveDevice; }

private:
    bool CheckKeyboardInputs();
    bool CheckGamepadInputs();

private:
    Device                   m_lastActiveDevice;
    int                      m_gamepadId;
    std::stack <InputLayer*> m_inputLayers;
    std::stack <Object*>     m_objectsStack;
};
