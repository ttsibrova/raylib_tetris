#pragma once
#include <graphics/drawable_object.h>
#include <graphics/colors.h>
#include <string>

namespace shapes {

class Shape: public DrawableObject
{
public:
    Shape():
        m_color (Colors::lightBlue)
    {}

    Color GetColor() const  { return { m_color.r, m_color.g, m_color.b, GetAlpha() }; }
    void SetColor (const Color& color) { m_color = color; m_alphaCh = m_color.a; }

    virtual void Translate (const Vector2& translation) override;

private:
    Color        m_color;
};

class Text: public Shape
{
public:
    Text (std::string str, int fontSize) :
        m_str (std::move (str)),
        m_fontSize (fontSize)
    {}

    void SetFontSize (int fontSize) { m_fontSize = fontSize; }
    int  GetFontSize () { return m_fontSize; }

    void UpdateText (const std::string& newText);

    virtual void Draw() const override;
    virtual BoundingBox2d GetBoundingBox() const override;
    virtual void Scale (float scale) override;

protected:
    std::string m_str;
    int         m_fontSize;
};

class ShadedText: public Text
{
public:
    ShadedText (const char* str, int fontSize, const Color& shadeColor):
        Text (str, fontSize),
        m_shadeColor (shadeColor)
    {}

    virtual void Draw() const override;

private:
    Color m_shadeColor;
};

class Rectangle: public Shape
{
public:
    Rectangle (float width, float height):
        m_width (width),
        m_height (height)
    {}
    Rectangle (const BoundingBox2d& bbox);

    virtual void Draw() const override;
    virtual BoundingBox2d GetBoundingBox() const override;
    virtual void Scale (float scale) override;

protected:
    float   m_width;
    float   m_height;
};

class RectangleRounded: public Rectangle
{
public:
    RectangleRounded (float width, float height, float roundness):
        Rectangle (width, height),
        m_roundness (roundness)
    {}
    RectangleRounded (const BoundingBox2d& bbox, float roundness):
        Rectangle (bbox),
        m_roundness (roundness)
    {}

    virtual void Draw() const override;

private:
    float m_roundness;
};

class Circle: public Shape
{
public:
    Circle (float radius):
        m_radius (radius)
    {}

    virtual void Draw() const override;
    virtual BoundingBox2d GetBoundingBox() const override;
    virtual void Scale (float scale) override;

private:
    float m_radius;
};


class Triangle: public Shape
{
public:
    Triangle (float height, float rot):
        m_height (height),
        m_rotation (rot)
    {}

    virtual void Draw() const override;
    virtual BoundingBox2d GetBoundingBox() const override;
    virtual void Scale (float scale) override;

private:
    float m_height;
    float m_rotation;
};
}
