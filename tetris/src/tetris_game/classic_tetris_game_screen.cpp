#include <tetris_game/classic_tetris_game_screen.h>

#include <graphics/colors.h>

ClassicTetrisGameScreen::ClassicTetrisGameScreen (const ScreenSize& screenSize):
    m_classicTetrisGame (&m_screenGraphics)
{
    m_screenGraphics.AddRectangle ({0.0},
        DrawPosition::TopLeft,
        screenSize.m_height * screenSize.m_scale,
        screenSize.m_width * screenSize.m_scale,
        Colors::darkBlue);
}

void ClassicTetrisGameScreen::Init()
{
    m_classicTetrisGame.Init();
    m_classicTetrisGame.Start();
}

void ClassicTetrisGameScreen::Tick()
{
    m_classicTetrisGame.Tick();
    m_screenGraphics.Draw();
    m_classicTetrisGame.Draw();
}



