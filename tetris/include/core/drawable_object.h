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

enum class DrawPosition
{
    Center,
    Right,
    Left,
    TopRight,
    Top,
    TopLeft,
    BottomRight,
    Bottom,
    BottomLeft
};

class DrawableObject
{
public:
    DrawableObject ():
        m_pos {0., 0.},
        m_align (DrawPosition::TopLeft)
    {}

protected:
    Vector2      m_pos;
    DrawPosition m_align;
};
