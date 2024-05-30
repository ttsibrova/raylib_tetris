#pragma once
#include <engine/game.h>
#include <engine/game_object.h>
#include <graphics/drawable_container.h>
#include <functional/observer.h>


struct ScreenSize {
    int   m_width;
    int   m_height;
    float m_scale = 1.0;
};

class Screen : public Object
{
public:
    void Draw() { m_screenGraphics.Draw(); }

protected:
    DrawableContainer m_screenGraphics;
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



