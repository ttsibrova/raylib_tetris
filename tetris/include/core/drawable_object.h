#pragma once
#include <core/bounding_box_2d.h>

class IDrawableObject
{
public:
    virtual void Draw() const = 0;
    virtual BoundingBox2d GetBoundingBox() const = 0;
    virtual void Translate (const Vector2& translation) = 0;
    virtual void Scale (float scale) = 0;
};
