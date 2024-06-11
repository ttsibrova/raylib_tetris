#pragma once
#include <engine/command.h>
#include <engine/game_object.h>
#include <graphics/drawable_container.h>


struct ScreenSize {
    int   m_width;
    int   m_height;
    float m_scale = 1.0;
};

enum class ScreenState {
    ACTIVE,
    SET_TO_CLOSE
};

class Screen : public GameObject
{
public:
    Screen ():
        m_state (ScreenState::ACTIVE)
    {}

    void Draw() { m_screenGraphics.Draw(); }
    void SetToClose() { m_state = ScreenState::SET_TO_CLOSE; }
    bool IsActive() { return m_state == ScreenState::ACTIVE; }

protected:
    ScreenState       m_state;
    DrawableContainer m_screenGraphics;
};

class ScreenCloseCommand: public CommandWithContext
{
public:
    ScreenCloseCommand (Screen* screen):
        CommandWithContext (screen)
    {}

    virtual bool Execute (Object* obj) override
    {
        if (auto screen = dynamic_cast <Screen*> (obj)) {
            screen->SetToClose();
            return true;
        }
        return false;
    }
};


class TitleScreen : public Screen
{
public:
    virtual void Tick() override;

};


class GameScreen : public Screen
{
public:

    virtual void Tick() override;

};



