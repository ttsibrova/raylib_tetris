#pragma once
#include <core/bounding_box_2d.h>
#include <engine/game_object.h>
#include <memory>

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

class DrawableObject: public Object
{
public:
    virtual ~DrawableObject() {}

    virtual void Draw() const = 0;
    virtual BoundingBox2d GetBoundingBox() const = 0;
    virtual void Translate (const Vector2& translation) = 0;
    virtual void Scale (float scale) = 0;

public:
    DrawableObject ():
        m_pos{0., 0.},
        m_align (DrawPosition::TopLeft),
        m_bIsVisible (true),
        m_alphaCh (255)
    {}

    void SetAlign (DrawPosition align) { m_align = align; }
    void SetVisible() { m_bIsVisible = true; }
    void SetInvisible() { m_bIsVisible = false; }
    bool IsVisible() const { return m_bIsVisible; }
    const Vector2 GetPosition() const { return m_pos; }
    virtual void SetAlpha (unsigned char alpha) { m_alphaCh = alpha; }
    unsigned char GetAlpha() const { return m_alphaCh; }

protected:
    void UpdatePosition (const BoundingBox2d& oldBBox, const BoundingBox2d& newBBox);

protected:
    Vector2       m_pos;
    DrawPosition  m_align;
    bool          m_bIsVisible;
    unsigned char m_alphaCh;
};

