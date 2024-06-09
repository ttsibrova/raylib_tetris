#include <graphics/drawable_container.h>
#include <graphics/graphics_helper.h>
#include <graphics/shapes.h>

void DrawableContainer::Draw() const
{
    for (const auto& obj : m_objects) {
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


DrawableObject* DrawableContainer::AddRectangle (
    Vector2 pixelPos,
    DrawPosition alignPos,
    float height, float width,
    const Color& color)
{
    auto Rectangle = std::make_unique <shapes::Rectangle> (width, height);
    Rectangle->SetAlign (alignPos);
    Rectangle->SetColor (color);

    auto bbox = Rectangle->GetBoundingBox();
    auto currentAdjustedPos = GraphicsHelper::ComputePosition (alignPos, bbox);
    Rectangle->Translate (GraphicsHelper::ComputeTranslation (currentAdjustedPos, pixelPos));
    m_objects.push_back (std::move (Rectangle));
    return m_objects.back().get();
}

DrawableObject* DrawableContainer::AddRectangle (
    Vector2 pixelPos,
    DrawPosition alignPos,
    const BoundingBox2d& bbox,
    const Color& color)
{
    auto Rectangle = std::make_unique <shapes::Rectangle> (bbox);
    Rectangle->SetAlign (alignPos);
    Rectangle->SetColor (color);

    auto currentAdjustedPos = GraphicsHelper::ComputePosition (alignPos, bbox);
    Rectangle->Translate (GraphicsHelper::ComputeTranslation (currentAdjustedPos, pixelPos));
    m_objects.push_back (std::move (Rectangle));
    return m_objects.back().get();
}

DrawableObject* DrawableContainer::AddRectangleRounded (
    Vector2 pixelPos,
    DrawPosition alignPos,
    int height,
    int width,
    float roundness,
    const Color& color)
{
    auto Rectangle = std::make_unique <shapes::RectangleRounded> (width, height, roundness);
    Rectangle->SetAlign (alignPos);
    Rectangle->SetColor (color);

    auto bbox = Rectangle->GetBoundingBox();
    auto currentAdjustedPos = GraphicsHelper::ComputePosition (alignPos, bbox);
    Rectangle->Translate (GraphicsHelper::ComputeTranslation (currentAdjustedPos, pixelPos));
    m_objects.push_back (std::move (Rectangle));
    return m_objects.back().get();
}

DrawableObject* DrawableContainer::AddText (
    Vector2 pixelPos,
    DrawPosition alignPos,
    const std::string& text,
    int fontSize,
    const Color& color)
{
    auto Text = std::make_unique <shapes::Text> (text, fontSize);
    Text->SetAlign (alignPos);
    Text->SetColor (color);

    auto bbox = Text->GetBoundingBox();
    auto currentAdjustedPos = GraphicsHelper::ComputePosition (alignPos, bbox);
    Text->Translate (GraphicsHelper::ComputeTranslation (currentAdjustedPos, pixelPos));
    m_objects.push_back (std::move (Text));
    return m_objects.back().get();
}

DrawableObject* DrawableContainer::AddShadedText (
    Vector2 pixelPos,
    DrawPosition alignPos,
    const std::string& text,
    int fontSize,
    const Color& color,
    const Color& shadeColor)
{
    auto Text = std::make_unique <shapes::ShadedText> (text.c_str(), fontSize, shadeColor);
    Text->SetAlign (alignPos);
    Text->SetColor (color);

    auto bbox = Text->GetBoundingBox();
    auto currentAdjustedPos = GraphicsHelper::ComputePosition (alignPos, bbox);
    Text->Translate (GraphicsHelper::ComputeTranslation (currentAdjustedPos, pixelPos));
    m_objects.push_back (std::move (Text));
    return m_objects.back().get();
}

DrawableObject* DrawableContainer::AddCircle (Vector2 pixelPos, DrawPosition align, float radius, const Color& color)
{
    auto circle = std::make_unique <shapes::Circle> (radius);
    circle->SetAlign (align);
    circle->SetColor (color);

    auto bbox = circle->GetBoundingBox();
    auto currentAdjustedPos = GraphicsHelper::ComputePosition (align, bbox);
    circle->Translate (GraphicsHelper::ComputeTranslation (currentAdjustedPos, pixelPos));
    m_objects.push_back (std::move (circle));
    return m_objects.back().get();
}

DrawableObject* DrawableContainer::AddTriangle (Vector2 pixelPos, DrawPosition align, float height, float rotation, const Color& color)
{
    auto tri = std::make_unique <shapes::Triangle> (height, rotation);
    tri->SetAlign (align);
    tri->SetColor (color);

    auto bbox = tri->GetBoundingBox();
    auto currentAdjustedPos = GraphicsHelper::ComputePosition (align, bbox);
    tri->Translate (GraphicsHelper::ComputeTranslation (currentAdjustedPos, pixelPos));
    m_objects.push_back (std::move (tri));
    return m_objects.back().get();
}

void DrawableContainer::AddDrawableObject (Vector2 pixelPos, DrawPosition alignPos, std::unique_ptr<DrawableObject>&& obj)
{
    auto bbox = obj->GetBoundingBox();
    auto currentAdjustedPos = GraphicsHelper::ComputePosition (alignPos, bbox);
    obj->SetAlign (alignPos);
    obj->Translate (GraphicsHelper::ComputeTranslation (currentAdjustedPos, pixelPos));
    m_objects.push_back (std::move (obj));
}

