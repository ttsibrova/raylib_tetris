#include <core/bounding_box_2d.h>

void BoundingBox2d::Expand (const BoundingBox2d& other)
{
    if (other.Min().x < m_min.x) {
        m_min.x = other.Min().x;
    }
    if (other.Min().y < m_min.y) {
        m_min.y = other.Min().y;
    }
    if (other.Max().x > m_max.x) {
        m_max.x = other.Max().x;
    }
    if (other.Max().y > m_max.y) {
        m_max.y = other.Max().y;
    }
}

BoundingBox2d BoundingBox2d::Translated (const Vector2& trl)
{
    return {{m_min.x + trl.x, m_min.y + trl.y}, {m_max.x + trl.x, m_max.y + trl.y}};
}

void BoundingBox2d::Translate (const Vector2& trl)
{
    m_min.x += trl.x; m_min.y += trl.y;
    m_max.x += trl.y; m_max.y += trl.y;
}


