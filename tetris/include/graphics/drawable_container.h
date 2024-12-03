#pragma once
#include <graphics/drawable_object.h>
#include <core/bounding_box_2d.h>

#include <vector>
#include <string>


class DrawableContainer: public DrawableObject
{
public:
    ~DrawableContainer();

public:
    DrawableObject* AddDrawableObject (Vector2 pixelPos, DrawPosition alignPos, DrawableObject* obj);

public:
    virtual void SetAlpha (unsigned char alpha) override;
    virtual void Draw() const override;
    virtual BoundingBox2d GetBoundingBox() const override;
    virtual void Translate (const Vector2& translation) override;
    virtual void Scale (float scale) override;

    bool IsEmpty() { return m_objects.empty(); }

protected:
    std::vector <DrawableObject*> m_objects;
};


namespace DrawableContainerTools
{
    DrawableObject* AddRectangle        (DrawableContainer& container, Vector2 pixelPos, DrawPosition align, const BoundingBox2d& bbox, const Color& color);
    DrawableObject* AddRectangleRounded (DrawableContainer& container, Vector2 pixelPos, DrawPosition align, int height, int widght, float roundness, const Color& color);
    DrawableObject* AddText             (DrawableContainer& container, Vector2 pixelPos, DrawPosition align, const std::string& text, int fontSize, const Color& color);
    DrawableObject* AddShadedText       (DrawableContainer& container, Vector2 pixelPos, DrawPosition align, const std::string& text, int fontSize, const Color& color, const Color& shadeColor);
    DrawableObject* AddRectangle        (DrawableContainer& container, Vector2 pixelPos, DrawPosition align, float height, float width, const Color& color);
    DrawableObject* AddCircle           (DrawableContainer& container, Vector2 pixelPos, DrawPosition align, float radius, const Color& color);
    DrawableObject* AddTriangle         (DrawableContainer& container, Vector2 pixelPos, DrawPosition align, float height, float rotation, const Color& color);
}

