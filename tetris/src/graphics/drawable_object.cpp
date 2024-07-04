#include <graphics/drawable_object.h>

#include <graphics/graphics_helper.h>


void DrawableObject::UpdatePosition (const BoundingBox2d& oldBBox, const BoundingBox2d& newBBox)
{
    Vector2 oldTargetPos = GraphicsHelper::ComputePosition (m_align, oldBBox);
    Vector2 newPos = GraphicsHelper::ComputePosition (m_align, newBBox);
    Translate (GraphicsHelper::ComputeTranslation (newPos, oldTargetPos));
}
