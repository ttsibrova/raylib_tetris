#pragma once
#include <graphics/drawable_object.h>
#include <core/bounding_box_2d.h>

#include <memory>
#include <vector>
#include <string>

class DrawableContainer: public DrawableObject
{
public:
    DrawableObject* AddRectangle (Vector2 pixelPos, DrawPosition alignPos, int height, int widght, const Color& color);
    DrawableObject* AddRectangle (Vector2 pixelPos, DrawPosition alignPos, const BoundingBox2d& bbox, const Color& color);
    DrawableObject* AddRectangleRounded (Vector2 pixelPos, DrawPosition alignPos, int height, int widght, float roundness, const Color& color);
    DrawableObject* AddText (Vector2 pixelPos, DrawPosition alignPos, const std::string& text, int fontSize, const Color& color);
    DrawableObject* AddShadedText (Vector2 pixelPos, DrawPosition alignPos, const std::string& text, int fontSize, const Color& color, const Color& shadeColor);

public:
    void AddDrawableObject (Vector2 pixelPos, DrawPosition alignPos, std::unique_ptr <DrawableObject>&& obj);
    //void AddDrawableObject (std::unique_ptr <DrawableObject>&& obj);

public:
    virtual void Draw() const override;
    virtual BoundingBox2d GetBoundingBox() const override;
    virtual void Translate (const Vector2& translation) override;
    virtual void Scale (float scale) override;

    bool IsEmpty() { return m_objects.empty(); }

protected:
    std::vector <std::unique_ptr <DrawableObject>> m_objects;
};

