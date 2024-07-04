#include <graphics/shapes.h>

#include <graphics/graphics_helper.h>

#include <algorithm>
#include <cmath>

namespace shapes {
void Shape::Translate (const Vector2& translation)
{
    m_pos.x += translation.x;
    m_pos.y += translation.y;
}

Rectangle::Rectangle (const BoundingBox2d& bbox)
{
    m_pos.x = bbox.Min().x;
    m_pos.y = bbox.Min().y;
    m_width = bbox.Max().x - bbox.Min().x;
    m_height = bbox.Max().y - bbox.Min().y;
}

void Rectangle::Draw() const
{
    DrawRectangleRec ({m_pos.x, m_pos.y, m_width, m_height}, GetColor());
}

BoundingBox2d Rectangle::GetBoundingBox() const
{
    //Raylib draws rectangles starting from TopLeft corner
    return BoundingBox2d (m_pos, {m_pos.x + m_width, m_pos.y + m_height});
}

void Rectangle::Scale (float scale)
{
    auto oldBBox = GetBoundingBox();
    m_height *= scale;
    m_width *= scale;
    auto newBBox = GetBoundingBox();

    UpdatePosition (oldBBox, newBBox);
}

void Text::UpdateText (const std::string& newText)
{
    auto oldBBox = GetBoundingBox();
    m_str = newText;
    auto newBBox = GetBoundingBox();

    UpdatePosition (oldBBox, newBBox);
}

void Text::Draw() const
{
    if (!m_str.empty())
        DrawText (m_str.c_str(), m_pos.x, m_pos.y, (int)m_fontSize, GetColor());
}

BoundingBox2d Text::GetBoundingBox() const
{
    //Raylib draws text starting from TopLeft corner
    int widght = MeasureText (m_str.c_str(), m_fontSize);
    return BoundingBox2d (m_pos, {m_pos.x + widght, m_pos.y + m_fontSize});
}

void Text::Scale (float scale)
{
    auto oldBBox = GetBoundingBox();
    m_fontSize *= scale;
    auto newBBox = GetBoundingBox();

    UpdatePosition (oldBBox, newBBox);
}

void ShadedText::Draw() const
{
    DrawText (m_str.c_str (), m_pos.x + 4, m_pos.y + 3, (int)m_fontSize + 2, {m_shadeColor.r, m_shadeColor.g, m_shadeColor.b, GetAlpha()});
    Text::Draw();
}

void RectangleRounded::Draw() const
{
    DrawRectangleRounded ({m_pos.x, m_pos.y, m_width, m_height}, m_roundness, 10, GetColor());
}

void Circle::Draw() const
{
    DrawCircle (m_pos.x, m_pos.y, m_radius, GetColor());
}

BoundingBox2d Circle::GetBoundingBox() const
{
    Vector2 min {m_pos.x - m_radius, m_pos.y - m_radius};
    Vector2 max {m_pos.x + m_radius, m_pos.y + m_radius};

    return {min, max};
}

void Circle::Scale (float scale)
{
    auto oldBBox = GetBoundingBox();
    m_radius *= scale;
    auto newBBox = GetBoundingBox();

    UpdatePosition (oldBBox, newBBox);
}


void Triangle::Draw() const
{
    DrawPoly (m_pos, 3, m_height * 2 / 3, m_rotation, GetColor());
}

BoundingBox2d Triangle::GetBoundingBox() const
{
    float rad = m_rotation * PI / 180;
    float R = m_height * 2 / 3;
    float pnt1X = m_pos.x + R * std::cos (rad);
    float pnt1Y = m_pos.y + R * std::sin (rad);
    rad += PI / 3 * 2; // +120 degree
    float pnt2X = m_pos.x + R * std::cos (rad);
    float pnt2Y = m_pos.y + R * std::sin (rad);
    rad += PI / 3 * 2; // +120 degree
    float pnt3X = m_pos.x + R * std::cos (rad);
    float pnt3Y = m_pos.y + R * std::sin (rad);

    float minX = std::min ({pnt1X, pnt2X, pnt3X});
    float minY = std::min ({pnt1Y, pnt2Y, pnt3Y});

    float maxX = std::max ({pnt1X, pnt2X, pnt3X});
    float maxY = std::max ({pnt1Y, pnt2Y, pnt3Y});

    return {{minX, minY}, {maxX, maxY}};
}

void Triangle::Scale (float scale)
{
    auto oldBBox = GetBoundingBox();
    m_height *= scale;
    auto newBBox = GetBoundingBox();

    UpdatePosition (oldBBox, newBBox);
}

}
