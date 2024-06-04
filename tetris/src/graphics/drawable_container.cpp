#include <graphics/drawable_container.h>
#include <graphics/shapes.h>


IDrawableObject* DrawableContainer::AddRectangle (
    Vector2 pixelPos,
    DrawPosition alignPos,
    int height, int widght,
    const Color& color)
{
    auto Rectangle = std::make_unique <shapes::Rectangle> (alignPos, widght, height);
    Rectangle->SetColor (color);

    auto bbox = Rectangle->GetBoundingBox();
    auto currentAdjustedPos = ComputePosition (alignPos, bbox);
    Rectangle->Translate (ComputeTranslation (currentAdjustedPos, pixelPos));
    m_objects.push_back (std::move (Rectangle));
    return m_objects.back().get();
}

IDrawableObject* DrawableContainer::AddRectangle (Vector2 pixelPos, DrawPosition alignPos, const BoundingBox2d& bbox, const Color& color)
{
    auto Rectangle = std::make_unique <shapes::Rectangle> (alignPos, bbox);
    Rectangle->SetColor (color);

    auto currentAdjustedPos = ComputePosition (alignPos, bbox);
    Rectangle->Translate (ComputeTranslation (currentAdjustedPos, pixelPos));
    m_objects.push_back (std::move (Rectangle));
    return m_objects.back().get();
}

IDrawableObject* DrawableContainer::AddRectangleRounded (Vector2 pixelPos, DrawPosition alignPos, int height, int width, float roundness, const Color& color)
{
    auto Rectangle = std::make_unique <shapes::RectangleRounded> (alignPos, height, width, roundness);
    Rectangle->SetColor (color);

    auto bbox = Rectangle->GetBoundingBox();
    auto currentAdjustedPos = ComputePosition (alignPos, bbox);
    Rectangle->Translate (ComputeTranslation (currentAdjustedPos, pixelPos));
    m_objects.push_back (std::move (Rectangle));
    return m_objects.back().get();
}

IDrawableObject* DrawableContainer::AddText (Vector2 pixelPos, DrawPosition alignPos, const std::string& text, int fontSize, const Color& color)
{
    auto Text = std::make_unique <shapes::Text> (alignPos, text, fontSize);
    Text->SetColor (color);

    auto bbox = Text->GetBoundingBox();
    auto currentAdjustedPos = ComputePosition (alignPos, bbox);
    Text->Translate (ComputeTranslation (currentAdjustedPos, pixelPos));
    m_objects.push_back (std::move (Text));
    return m_objects.back().get();
}

IDrawableObject* DrawableContainer::AddShadedText (Vector2 pixelPos,
                                       DrawPosition alignPos,
                                       const std::string& text,
                                       int fontSize,
                                       const Color& color,
                                       const Color& shadeColor)
{
    auto Text = std::make_unique <shapes::ShadedText> (alignPos, text.c_str(), fontSize, shadeColor);
    Text->SetColor (color);

    auto bbox = Text->GetBoundingBox();
    auto currentAdjustedPos = ComputePosition (alignPos, bbox);
    Text->Translate (ComputeTranslation (currentAdjustedPos, pixelPos));
    m_objects.push_back (std::move (Text));
    return m_objects.back().get();
}

void DrawableContainer::AddDrawableObject (Vector2 pixelPos, DrawPosition alignPos, std::unique_ptr<IDrawableObject>&& obj)
{
    auto bbox = obj->GetBoundingBox();
    auto currentAdjustedPos = ComputePosition (alignPos, bbox);
    obj->Translate (ComputeTranslation (currentAdjustedPos, pixelPos));
    m_objects.push_back (std::move (obj));
}

void DrawableContainer::AddDrawableObject (std::unique_ptr<IDrawableObject>&& obj)
{
    m_objects.push_back (std::move (obj));
}

DrawableContainer* DrawableContainer::RegisterEmptyContainer()
{
    auto newContainer = std::make_unique <DrawableContainer>();
    DrawableContainer* rawPtr = newContainer.get();
    m_objects.push_back (std::move (newContainer));
    return rawPtr;
}

void DrawableContainer::Draw (Vector2 pixelPos, DrawPosition alignPos) const
{
    auto containerBBox = GetBoundingBox();

    auto currentAdjustedPos = ComputePosition (alignPos, containerBBox);
    auto translation = ComputeTranslation (currentAdjustedPos, pixelPos);
    for (auto& obj : m_objects) {
        obj->Translate (translation);
        obj->Draw();
    }
}

void DrawableContainer::Draw() const
{
    for (const auto& obj: m_objects) {
        obj->Draw();
    }
}

BoundingBox2d DrawableContainer::GetBoundingBox() const
{
    BoundingBox2d containerBBox;
    if (m_objects.size() > 0) {
        containerBBox = m_objects.front()->GetBoundingBox();
    }
    for (auto& obj : m_objects) {
        containerBBox.Expand (obj->GetBoundingBox());
    }
    return containerBBox;
}

void DrawableContainer::Translate (const Vector2& translation)
{
    for (auto& obj : m_objects) {
        obj->Translate (translation);
    }
}

void DrawableContainer::Scale (float scale)
{
    for (auto& obj : m_objects) {
        obj->Scale (scale);
    }
}

Vector2 DrawableContainer::ComputePosition (DrawPosition alignPos, const BoundingBox2d& bbox)
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

Vector2 DrawableContainer::ComputeTranslation (const Vector2& from, const Vector2& to) {
    return {to.x - from.x, to.y - from.y};
}
