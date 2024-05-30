#pragma once
#include <core/drawable_object.h>

#include <memory>
#include <vector>
#include <string>

enum class DrawPosition
{
    Center,
    Right,
    Left,
    TopRight,
    Top,
    TopLeft,
    BottomRight,
    Bottom,
    BottomLeft
};

class DrawableContainer : public IDrawableObject
{
public:

    IDrawableObject* AddRectangle (Vector2 pixelPos, DrawPosition alignPos, int height, int widght, const Color& color);
    IDrawableObject* AddRectangle (Vector2 pixelPos, DrawPosition alignPos, const BoundingBox2d& bbox, const Color& color);
    IDrawableObject* AddText (Vector2 pixelPos, DrawPosition alignPos, const std::string& text, int fontSize, const Color& color);
    IDrawableObject* AddShadedText (Vector2 pixelPos, DrawPosition alignPos, const std::string& text, int fontSize, const Color& color, const Color& shadeColor);

    void AddDrawableObject (Vector2 pixelPos, DrawPosition alignPos, std::unique_ptr <IDrawableObject>&& obj);
    void AddDrawableObject (std::unique_ptr <IDrawableObject>&& obj);
    DrawableContainer* RegisterEmptyContainer();

    void AppendContainer (Vector2 pixelPos, DrawPosition alignPos, DrawableContainer&& other);

    void Draw (Vector2 pixelPos, DrawPosition alignPos) const;
    virtual void Draw() const override;
    virtual BoundingBox2d GetBoundingBox() const override;
    virtual void Translate (const Vector2& translation) override;
    virtual void Scale (float scale) override;

    bool IsEmpty() { return m_objects.empty(); }

    static Vector2 ComputePosition (DrawPosition alignPos, const BoundingBox2d& bbox);
    static Vector2 ComputeTranslation (const Vector2& from, const Vector2& to);

private:
    std::vector <std::unique_ptr <IDrawableObject>> m_objects;
};
