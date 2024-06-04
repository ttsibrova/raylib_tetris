#include <graphics/shapes.h>
namespace shapes {

void Shape::UpdatePosition (const BoundingBox2d& oldBBox, const BoundingBox2d& newBBox)
{
    Vector2 oldTargetPos = DrawableContainer::ComputePosition (m_align, oldBBox);
    Vector2 newPos = DrawableContainer::ComputePosition (m_align, newBBox);

    Translate (DrawableContainer::ComputeTranslation (newPos, oldTargetPos));
}

Rectangle::Rectangle (DrawPosition align, const BoundingBox2d& bbox):
    Shape (align)
{
    m_pos.x = bbox.Min().x;
    m_pos.y = bbox.Min().y;
    m_width = bbox.Max().x - bbox.Min().x;
    m_height = bbox.Max().y - bbox.Min().y;
}

void Rectangle::Draw() const
{
    DrawRectangle (m_pos.x, m_pos.y, m_width, m_height, GetColor());
}

BoundingBox2d Rectangle::GetBoundingBox() const
{
    //Raylib draws rectangles starting from TopLeft corner
    return BoundingBox2d (m_pos, {m_pos.x + m_width, m_pos.y + m_height});
}

void Rectangle::Translate (const Vector2& translation)
{
    m_pos.x += translation.x;
    m_pos.y += translation.y;
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

void Text::Translate (const Vector2& translation)
{
    m_pos.x += translation.x;
    m_pos.y += translation.y;
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
    DrawText (m_str.c_str(), m_pos.x + 4, m_pos.y + 3, (int)m_fontSize+2, m_shadeColor);
    Text::Draw();
}

void RectangleRounded::Draw() const
{
    DrawRectangleRounded ({m_pos.x, m_pos.y, m_width, m_height}, m_roundness, 10, GetColor());
}

}
