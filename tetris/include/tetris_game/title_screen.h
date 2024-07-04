#pragma once
#include <engine/screen.h>

class Animation;

class TitleScreen: public Screen
{
public:
    TitleScreen (InputHandler* iHandler, const ScreenSize& screenSize);

    virtual void Tick() override;

private:
    size_t                   m_animIdx;
    std::vector <Animation*> m_animsLogo;
    Animation*               m_animPress;
    std::vector <Animation*> m_animsBlocks;
};

