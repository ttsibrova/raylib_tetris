#pragma once
#include <core/drawable_object.h>
#include <graphics/drawable_container.h>
#include <functional/colors.h>
#include <string>
#include <optional>

namespace shapes {

class Shape: public IDrawableObject
{
public:
    Shape ():
        m_pos{0., 0.},
        m_align (DrawPosition::TopLeft),
        m_color (Colors::lightBlue)
    {}
    Shape (const Vector2& pos, DrawPosition align):
        m_pos (pos),
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
    Text (const std::string& str, int fontSize):
        m_str (str),
        m_fontSize (fontSize)
    {}
    Text (const char* str, int fontSize):
        m_str (str),
        m_fontSize (fontSize)
    {}

    Text (const Vector2& pos, DrawPosition align, const char* str, int fontSize) :
        Shape (pos, align),
        m_str (str),
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
    ShadedText (const Vector2& pos, DrawPosition align, const char* str, int fontSize, const Color& shadeColor):
        Text (pos, align, str, fontSize),
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
    Rectangle (const Vector2& pos, DrawPosition align, float width, float height):
        Shape (pos, align),
        m_width (width),
        m_height (height)
    {}
    Rectangle (const BoundingBox2d& bbox);

    virtual void Draw() const override;
    virtual BoundingBox2d GetBoundingBox() const override;
    virtual void Translate (const Vector2& translation) override;
    virtual void Scale (float scale) override;

private:
    float   m_width;
    float   m_height;
};

class Cell: public Shape
{
public:


private:
    int     m_cellSize;
    Color m_mainColor;
    Color m_internalShadeColor;

    std::optional <Color> m_outlineColor;
    std::optional <Color> m_externalShadeColor;
};

class Triangle: public Shape
{

private:

};
}
