#include <ui/ui_mapped_key.h>

#include <graphics/drawable_container.h>
#include <graphics/sprites.h>

MappedKey::MappedKey (KeyboardKey key, GamepadButton button, float size)
{
    m_gamepadGraphics = SpriteGraphicGenerator::GetXBoxButton (button, size);
    m_keyboardGraphics = SpriteGraphicGenerator::GetKeybordKey (key, size);
}

MappedKey::~MappedKey()
{
    if (m_gamepadGraphics) {
        delete m_gamepadGraphics;
    }
    if (m_keyboardGraphics) {
        delete m_keyboardGraphics;
    }
}


void MappedKey::Draw() const
{
    switch (InputHandler::GlobalInstance().GetActiveDevice())
    {
    case Device::KEYBOARD:
        m_keyboardGraphics->Draw();
        break;
    case Device::GAMEPAD:
        m_gamepadGraphics->Draw();
        break;
    }
}

BoundingBox2d MappedKey::GetBoundingBox() const
{
    auto bbox = m_keyboardGraphics->GetBoundingBox();
    //bbox.Expand (m_gamepadGraphics->GetBoundingBox());
    return bbox;
}

void MappedKey::Translate (const Vector2& translation)
{
    m_keyboardGraphics->Translate (translation);
    m_gamepadGraphics->Translate (translation);
}

void MappedKey::Scale (float scale)
{
    m_keyboardGraphics->Scale (scale);
    m_gamepadGraphics->Scale (scale);
}
