#pragma once
#include <engine/screen.h>
#include <functional/events.h>


class ClassicTetrisGameScreen: public Screen, IObserver <ClassicTetrisGameScreenEvent>
{
public:

    ClassicTetrisGameScreen (const ScreenSize& screenSize);

    void Init ();
    virtual void Tick() override;

    virtual void onNotify (const Object& obj, Event e) override {}

private:
    Game m_classicTetrisGame;
};
