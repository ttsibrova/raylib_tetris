#include <graphics/drawable_object_with_container.h>

#include <graphics/graphics_helper.h>

// DrawableObject interface
void DrawableObjectWithContainer::Draw() const
{
    if (IsVisible()) {
        m_graphics.Draw();
    }
}

BoundingBox2d DrawableObjectWithContainer::GetBoundingBox() const
{
    return m_graphics.GetBoundingBox();
}

void DrawableObjectWithContainer::Translate (const Vector2& translation)
{
    m_graphics.Translate (translation);
}

void DrawableObjectWithContainer::Scale (float scale)
{
    m_graphics.Scale (scale);
}

