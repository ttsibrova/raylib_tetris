#pragma once
#include <graphics/sprites.h>
#include <engine/command.h>
#include <ui/ui_menu_element.h>

class Button :public MenuElement
{
public:
    Button (const std::string& name, float width, std::unique_ptr <CommandWithContext>&& interaction):
        MenuElement (std::move (interaction))
    {
        m_grahicsButton = SpriteGraphicGenerator::GetButton (name, width);
        m_grahicsSelected = SpriteGraphicGenerator::GetButtonHover (name, width);
        m_grahicsPressed = SpriteGraphicGenerator::GetButtonPressed (name, width);
    }
    ~Button();

    bool IsClicked();

    virtual void Draw() const;
    virtual BoundingBox2d GetBoundingBox() const;
    virtual void Translate (const Vector2& translation);
    virtual void Scale (float scale);

private:
    DrawableObject* m_grahicsButton;
    DrawableObject* m_grahicsSelected;
    DrawableObject* m_grahicsPressed;
};
