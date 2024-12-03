#pragma once
#include <graphics/drawable_object.h>
#include <engine/input_handler.h>

class MappedKey: public DrawableObject
{
public:
    MappedKey (KeyboardKey key, GamepadButton button, float size);
    ~MappedKey();

    virtual void Draw() const override;
    virtual BoundingBox2d GetBoundingBox() const override;
    virtual void Translate (const Vector2& translation) override;
    virtual void Scale (float scale) override;

private:
    DrawableObject*     m_keyboardGraphics;
    DrawableObject*     m_gamepadGraphics;
};

