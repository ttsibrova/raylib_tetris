#pragma once
#include <core/drawable_object.h>
#include <graphics/drawable_container.h>
#include <engine/game_object.h>

class GraphicsComponent
{
public:
    GraphicsComponent (DrawableContainer* container): 
        m_graphics (container)
    {}

    void RegisterGraphic () {

    }
    //virtual void Tick() override;

private:
    DrawableContainer* m_graphics;
};
