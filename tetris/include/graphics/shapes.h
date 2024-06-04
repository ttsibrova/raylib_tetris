#pragma once
#include <core/drawable_object.h>
#include <graphics/drawable_container.h>
#include <functional/colors.h>
#include <string>

namespace shapes {

class Shape: public IDrawableObject
{
public:
    Shape (DrawPosition align):
        m_pos {0., 0.},
        m_align (align),
        m_color (Colors::lightBlue)
    {}

    const Color& GetColor() const  { return m_color; }
    void SetColor (const Color& color) { m_color = color; }

protected:
    void UpdatePosition (const BoundingBox2d& oldBBox, const BoundingBox2d& newBBox);

protected:
    Vector2      m_pos;
    DrawPosition m_align;
private:
    Color        m_color;
};

class Text: public Shape
{
public:
    Text (DrawPosition align, std::string str, int fontSize) :
        Shape (align),
        m_str (std::move (str)),
        m_fontSize (fontSize)
    {}

    void SetFontSize (int fontSize) { m_fontSize = fontSize; }
    int  GetFontSize () { return m_fontSize; }

    void UpdateText (const std::string& newText);

    virtual void Draw() const override;
    virtual BoundingBox2d GetBoundingBox() const override;
    virtual void Translate (const Vector2& translation) override;
    virtual void Scale (float scale) override;

protected:
    std::string m_str;
    int         m_fontSize;
};

class ShadedText: public Text
{
public:
    ShadedText (DrawPosition align, const char* str, int fontSize, const Color& shadeColor):
        Text (align, str, fontSize),
        m_shadeColor (shadeColor)
    {}

    virtual void Draw() const override;

private:
    Color m_shadeColor;
};

class Rectangle: public Shape
{
public:
    Rectangle (DrawPosition align, float width, float height):
        Shape (align),
        m_width (width),
        m_height (height)
    {}
    Rectangle (DrawPosition align, const BoundingBox2d& bbox);

    virtual void Draw() const override;
    virtual BoundingBox2d GetBoundingBox() const override;
    virtual void Translate (const Vector2& translation) override;
    virtual void Scale (float scale) override;

protected:
    float   m_width;
    float   m_height;
};

class RectangleRounded: public Rectangle
{
public:
    RectangleRounded (DrawPosition align, float width, float height, float roundness):
        Rectangle (align, width, height),
        m_roundness (roundness)
    {}
    RectangleRounded (DrawPosition align, const BoundingBox2d& bbox, float roundness):
        Rectangle (align, bbox),
        m_roundness (roundness)
    {}

    virtual void Draw() const override;

private:
    float m_roundness;
};


class Triangle: public Shape
{

private:

};
}
