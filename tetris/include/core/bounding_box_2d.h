#pragma once
#include <raylib/raylib.h>

class BoundingBox2d
{
public:
    BoundingBox2d ():
        m_min {0., 0.},
        m_max {0., 0.}
    {}

    BoundingBox2d (const Vector2& min, const Vector2& max):
        m_min (min),
        m_max (max)
    {}

    const Vector2& Min() const { return m_min; }
    const Vector2& Max() const { return m_max; }

    float Width () const { return m_max.x - m_min.x; }
    float Height() const { return m_max.y - m_min.y; }

    void Expand (const BoundingBox2d& other);
    BoundingBox2d Translated (const Vector2& trl);
    void Translate (const Vector2& trl);

private:
    Vector2 m_min;
    Vector2 m_max;
};
