#pragma once
#include <graphics/drawable_object.h>
#include <graphics/drawable_container.h>
#include <graphics/shapes.h>

class UIGroupContainer: public shapes::Rectangle
{
public:
    UIGroupContainer (const BoundingBox2d& boundaries):
        shapes::Rectangle (boundaries)
    {}

    UIGroupContainer (const Vector2& minCorner, const Vector2 maxCorner):
        shapes::Rectangle ({minCorner, maxCorner})
    {}

    virtual void Draw() const override {} //Has no graphics formally
};
