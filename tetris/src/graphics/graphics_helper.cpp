#include <graphics/graphics_helper.h>


Vector2 GraphicsHelper::ComputePosition (DrawPosition alignPos, const BoundingBox2d& bbox)
{
    float height = bbox.Max().y - bbox.Min().y;
    float width = bbox.Max().x - bbox.Min().x;

    switch (alignPos)
    {
    case DrawPosition::Center:
        return {bbox.Min().x + width / 2, bbox.Min().y + height / 2};
    case DrawPosition::Right:
        return {bbox.Max().x, bbox.Min().y + height / 2};
    case DrawPosition::Left:
        return {bbox.Min().x, bbox.Min().y + height / 2};
    case DrawPosition::TopRight:
        return {bbox.Max().x, bbox.Min().y};
    case DrawPosition::Top:
        return {bbox.Min().x + width / 2, bbox.Min().y};
    case DrawPosition::TopLeft:
        return bbox.Min();
    case DrawPosition::BottomRight:
        return bbox.Max();
    case DrawPosition::Bottom:
        return {bbox.Min().x + width / 2, bbox.Max().y};
    case DrawPosition::BottomLeft:
        return {bbox.Min().x, bbox.Max().y};
    default:
        break;
    }
    return {0., 0.};
}

Vector2 GraphicsHelper::ComputeTranslation (const Vector2& from, const Vector2& to) {
    return {to.x - from.x, to.y - from.y};
}

