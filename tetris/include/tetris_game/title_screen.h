#pragma once
#include <engine/screen.h>

class Animation;

class TitleScreen: public Screen
{
public:
    TitleScreen (InputHandler* iHandler, const ScreenSize& screenSize);
    ~TitleScreen();

    virtual void Tick() override;
    void SetReady() { m_bIsreadyForGame = true; }

private:
    size_t                   m_animIdx;
    std::vector <Animation*> m_animsLogo;
    Animation*               m_animPress;
    std::vector <Animation*> m_animsBlocks;
    Animation*               m_screenExitAnimation;
    bool                     m_bIsreadyForGame;

};

class SetReadyCommand: public CommandWithContext
{
public:
    SetReadyCommand (Screen* currentScreen):
        CommandWithContext (currentScreen)
    {}

    virtual bool Execute (Object* obj) override
    {
        if (auto screen = dynamic_cast <TitleScreen*> (obj)) {
            screen->SetReady();
            return true;
        }
        return false;
    }

private:
    Screens m_nextScreen;
};

