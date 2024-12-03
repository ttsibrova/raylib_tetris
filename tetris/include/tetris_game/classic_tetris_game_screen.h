#pragma once
#include <engine/screen.h>
#include <engine/events.h>
#include <engine/observer.h>
#include <ui/ui_menu.h>
#include <tetris_game/classic_tetris_game.h>
#include <tetris_game/highscores.h>
#include <engine/input_handler.h>


class ClassicTetrisGameScreen: public Screen, IObserver <ClassicTetrisGameScreenEvent>
{
public:

    class PauseSubScreen: public Screen, public Subject <CTGSObserver>
    {
    public:
        PauseSubScreen (const ScreenSize& size,
                        Vector2 posCenter,
                        const settings::KeyboardMappings& kMap,
                        const settings::GamepadMappings& gMap);

        void NotifyGameReset();

        virtual void Update() override {}
        virtual ~PauseSubScreen();
    private:
        Menu*         m_pauseMenu;
        InputLayer    m_inputLayer;
    };

    class GameOverSubScreen: public Screen, public Subject <CTGSObserver>
    {
    public:
        GameOverSubScreen (const ScreenSize& size,
                           Vector2 posCenter,
                           size_t score);

        void NotifyGameReset();

        virtual void Update() override {}
        virtual ~GameOverSubScreen();
    private:
        Menu*      m_gameOverMenu;
        InputLayer m_inputLayer;
    };

    ClassicTetrisGameScreen (const ScreenSize& screenSize);
    ~ClassicTetrisGameScreen();

    virtual void Update() override;
    virtual void onNotify (const Object& obj, Event e) override;

    const HighScores& GetGameHighScores() const { return m_gameScores; }

private:
    PauseSubScreen*    m_pauseScreen;
    GameOverSubScreen* m_gameOverScreen;
    HighScores         m_gameScores;
    ClassicTetrisGame  m_classicTetrisGame;
    ScreenSize         m_screenSize;
};

class Animation;

class CTGHighScoresScreen: public Screen
{
public:
    CTGHighScoresScreen (const ScreenSize& size,
                         HighScores scores);

    virtual void Update() override;

    virtual ~CTGHighScoresScreen();
private:
    Menu*                   m_menu;
    InputLayer              m_inputLayer;
    std::vector<Animation*> m_anims;
};

