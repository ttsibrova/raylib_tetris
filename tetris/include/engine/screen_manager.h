#pragma once
#include <engine/input_handler.h>

class Screen;

enum class Screens
{
    NONE,
    MAIN_MENU,
    TETRIS_GAME,
    SETTINGS
};

struct ScreenSize {
    int   m_width;
    int   m_height;
    float m_scale = 1.0;
};

class ScreenManager : public GameObject
{
public:
    ScreenManager (const ScreenSize& screenSize);

    virtual void Tick() override;
    bool ShouldClose() { return m_bShouldClose; }

    ~ScreenManager();

private:
    std::unique_ptr <InputHandler>   m_inputHandler;
    ScreenSize                       m_screenSize;
    Screens                          m_currentState;
    Screen*                          m_currentScreen;
    bool                             m_bShouldClose;
};

