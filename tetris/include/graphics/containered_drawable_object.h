#pragma once
#include <graphics/drawable_object.h>
#include <graphics/drawable_container.h>

class ContaineredDrawableObject: public DrawableObject
{
public:
    ContaineredDrawableObject ():
        m_graphics (std::make_unique <DrawableContainer> ())
    {}

    // DrawableObject interface
    virtual void Draw () const override;
    virtual BoundingBox2d GetBoundingBox () const override;
    virtual void Translate (const Vector2& translation) override;
    virtual void Scale (float scale) override;

protected:
    std::unique_ptr <DrawableContainer> m_graphics;
};
