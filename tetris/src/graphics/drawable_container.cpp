#include <graphics/drawable_container.h>
#include <graphics/graphics_helper.h>
#include <graphics/shapes.h>

void DrawableContainer::SetAlpha (unsigned char alpha)
{
    m_alphaCh = alpha;
    for (const auto& obj : m_objects) {
        obj->SetAlpha (GetAlpha());
        obj->Draw();
    }
}

void DrawableContainer::Draw() const
{
    if (!IsVisible())
    {
        return;
    }
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
    m_pos.x += translation.x;
    m_pos.y += translation.y;
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


DrawableContainer::~DrawableContainer()
{
    for (auto obj : m_objects) {
        if (obj) {
            delete obj;
            obj = nullptr;
        }
    }
}

DrawableObject* DrawableContainerTools::AddRectangle (
    DrawableContainer& container,
    Vector2 pixelPos,
    DrawPosition alignPos,
    float height, float width,
    const Color& color)
{
    auto rectangle = new shapes::Rectangle (width, height);
    rectangle->SetColor (color);
    return container.AddDrawableObject (pixelPos, alignPos, rectangle);
}

DrawableObject* DrawableContainerTools::AddRectangle (
    DrawableContainer& container,
    Vector2 pixelPos,
    DrawPosition alignPos,
    const BoundingBox2d& bbox,
    const Color& color)
{
    auto rectangle = new shapes::Rectangle (bbox);
    rectangle->SetColor (color);
    return container.AddDrawableObject (pixelPos, alignPos, rectangle);
}

DrawableObject* DrawableContainerTools::AddRectangleRounded (
    DrawableContainer& container,
    Vector2 pixelPos,
    DrawPosition alignPos,
    int height,
    int width,
    float roundness,
    const Color& color)
{
    auto rectangle = new shapes::RectangleRounded (width, height, roundness);
    rectangle->SetColor (color);
    return container.AddDrawableObject (pixelPos, alignPos, rectangle);
}

DrawableObject* DrawableContainerTools::AddText (
    DrawableContainer& container,
    Vector2 pixelPos,
    DrawPosition alignPos,
    const std::string& text,
    int fontSize,
    const Color& color)
{
    auto textSh = new shapes::Text (text, fontSize);
    textSh->SetColor (color);
    return container.AddDrawableObject (pixelPos, alignPos, textSh);
}

DrawableObject* DrawableContainerTools::AddShadedText (
    DrawableContainer& container,
    Vector2 pixelPos,
    DrawPosition alignPos,
    const std::string& text,
    int fontSize,
    const Color& color,
    const Color& shadeColor)
{
    auto textSh = new shapes::ShadedText (text.c_str(), fontSize, shadeColor);
    textSh->SetColor (color);
    return container.AddDrawableObject (pixelPos, alignPos, textSh);
}

DrawableObject* DrawableContainerTools::AddCircle (
    DrawableContainer& container,
    Vector2 pixelPos,
    DrawPosition align,
    float radius,
    const Color& color)
{
    auto circle = new shapes::Circle (radius);
    circle->SetColor (color);
    return container.AddDrawableObject (pixelPos, align, circle);
}

DrawableObject* DrawableContainerTools::AddTriangle (
    DrawableContainer& container,
    Vector2 pixelPos,
    DrawPosition align,
    float height,
    float rotation,
    const Color& color)
{
    auto tri = new shapes::Triangle (height, rotation);
    tri->SetColor (color);
    return container.AddDrawableObject (pixelPos, align, tri);
}

DrawableObject* DrawableContainer::AddDrawableObject (Vector2 pixelPos, DrawPosition alignPos, DrawableObject* obj)
{
    obj->SetAlign (alignPos);
    auto bbox = obj->GetBoundingBox();
    auto currentAdjustedPos = GraphicsHelper::ComputePosition (alignPos, bbox);
    obj->Translate (GraphicsHelper::ComputeTranslation (currentAdjustedPos, pixelPos));
    m_objects.push_back (obj);
    return obj;
}

