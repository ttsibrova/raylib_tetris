#pragma once
#include <graphics/drawable_object.h>
#include <graphics/drawable_container.h>

class DrawableObjectWithContainer: public DrawableObject
{
public:
    DrawableObjectWithContainer()
    {}

    // DrawableObject interface
    virtual void Draw() const override;
    virtual BoundingBox2d GetBoundingBox() const override;
    virtual void Translate (const Vector2& translation) override;
    virtual void Scale (float scale) override;

protected:
    DrawableContainer m_graphics;
};
