#pragma once
#include <engine/command.h>
#include <engine/game_object.h>
#include <engine/screen_manager.h>
#include <graphics/drawable_container.h>


enum class ScreenState {
    ACTIVE,
    SET_TO_CLOSE
};

class Screen : public GameObject
{
public:
    Screen (InputHandler* iHandler):
        m_state (ScreenState::ACTIVE),
        m_inputHandler (iHandler),
        m_nextScreen {false, Screens::NONE}
    {}

    void Draw() { m_screenGraphics.Draw(); }
    void SetToClose() { m_state = ScreenState::SET_TO_CLOSE; }
    bool IsActive() { return m_state == ScreenState::ACTIVE; }
    bool DoesWantToChangeScreen() { return m_nextScreen.first; }
    Screens GetNextScreen() { return m_nextScreen.second;}
    void SetNextScreen (Screens nextScreen) { m_nextScreen.first = true; m_nextScreen.second = nextScreen; }

protected:
    ScreenState               m_state;
    DrawableContainer         m_screenGraphics;
    InputHandler*             m_inputHandler;
    std::pair <bool, Screens> m_nextScreen;
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

class ScreenChangeCommand: public CommandWithContext
{
public:
    ScreenChangeCommand (Screens nextScreen, Screen* currentScreen):
        CommandWithContext (currentScreen),
        m_nextScreen (nextScreen)
    {}

    virtual bool Execute (Object* obj) override
    {
        if (auto screen = dynamic_cast <Screen*> (obj)) {
            screen->SetNextScreen (m_nextScreen);
            return true;
        }
        return false;
    }

private:
    Screens m_nextScreen;
};

class MainMenuScreen : public Screen
{
public:
    MainMenuScreen (InputHandler* iHandler, const ScreenSize& screenSize);
    ~MainMenuScreen();
    virtual void Tick() override;
};


class GameScreen : public Screen
{
public:

    virtual void Tick() override;

};



