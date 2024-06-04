#pragma once
#include <graphics/shapes.h>
#include <graphics/drawable_container.h>

class UIGroupContainer: public shapes::Rectangle
{
public:
    UIGroupContainer (DrawPosition align, const BoundingBox2d& boundaries):
        shapes::Rectangle (align, boundaries)
    {}

    UIGroupContainer (DrawPosition align, const Vector2& minCorner, const Vector2 maxCorner):
        shapes::Rectangle (align, BoundingBox2d (minCorner, maxCorner))
    {}

    virtual void Draw() const override {} //Has no graphics formally
};
