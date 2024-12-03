#pragma once

enum class Screens
{
    NONE,
    MAIN_MENU,
    TITLE,
    TETRIS_GAME,
    TETRIS_HIGHSCORES,
    TETRIS_PAUSE,
    TETRIS_GAMEOVER,
    SETTINGS
};

struct ScreenSize {
    int   m_width;
    int   m_height;
    float m_scale = 1.0;
};




