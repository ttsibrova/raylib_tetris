#pragma once
#include <engine/screen.h>
#include <engine/events.h>
#include <engine/observer.h>
#include <ui/ui_menu.h>
#include <tetris_game/classic_tetris_game.h>
#include <engine/input_handler.h>


class ClassicTetrisGameScreen: public Screen, IObserver <ClassicTetrisGameScreenEvent>
{
public:

    class PauseSubScreen: public Screen
    {
    public:
        PauseSubScreen (const ScreenSize& size,
                        Vector2 posCenter,
                        InputHandler* iHandler,
                        const Settings::KeyboardMappings& kMap,
                        const Settings::GamepadMappings& gMap);
        virtual void Tick() override {}
        virtual ~PauseSubScreen();
    private:
        Menu*         m_pauseMenu;
        InputLayer    m_inputLayer;
    };

    ClassicTetrisGameScreen (const ScreenSize& screenSize, InputHandler* iHandler);

    //void Init();
    virtual void Tick() override;
    virtual void onNotify (const Object& obj, Event e) override;

private:
    PauseSubScreen*   m_pauseScreen;
    ClassicTetrisGame m_classicTetrisGame;
    ScreenSize        m_screenSize;
};
