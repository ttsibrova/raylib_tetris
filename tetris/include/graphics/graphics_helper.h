#pragma once
#include <graphics/drawable_object.h>

class GraphicsHelper
{
public:
    static Vector2 ComputePosition (DrawPosition alignPos, const BoundingBox2d& bbox);
    static Vector2 ComputeTranslation (const Vector2& from, const Vector2& to);
};
