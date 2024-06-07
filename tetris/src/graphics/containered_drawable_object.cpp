#include <graphics/containered_drawable_object.h>

#include <graphics/graphics_helper.h>

// DrawableObject interface
void ContaineredDrawableObject::Draw() const
{
    m_graphics->Draw();
}

BoundingBox2d ContaineredDrawableObject::GetBoundingBox() const
{
    return m_graphics->GetBoundingBox();
}

void ContaineredDrawableObject::Translate (const Vector2& translation)
{
    m_graphics->Translate (translation);
}

void ContaineredDrawableObject::Scale (float scale)
{
    m_graphics->Scale (scale);
}

