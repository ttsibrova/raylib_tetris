#pragma once
#include <graphics/drawable_container.h>
#include <graphics/sprites.h>

#include <engine/command.h>
#include <engine/event_timer_handler.h>

#include <ui/ui_menu_element.h>


class ButtonDelayedCommand: public CommandWithContext
{
public:
    ButtonDelayedCommand (CommandWithContext* interaction) :
        CommandWithContext (nullptr),
        m_interaction (interaction)
    {}

    virtual bool Execute (Object* /*obj*/) {
        EventTimerHandler::GetInstance().AddTimer (0.08f, m_interaction);
        return true;
    }

private:
    CommandWithContext* m_interaction;
};


class Button :public MenuElement
{
public:
    Button (const std::string& name, float width, std::unique_ptr <CommandWithContext>&& interaction):
        MenuElement (std::make_unique<ButtonDelayedCommand> (interaction.get())),
        m_interaction (std::move (interaction))
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

    std::unique_ptr <CommandWithContext> m_interaction;
};
