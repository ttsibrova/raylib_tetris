#pragma once
#include <engine/command.h>
#include <graphics/drawable_object.h>


class MenuElement: public DrawableObject
{
public:
    MenuElement (std::unique_ptr <CommandWithContext>&& interaction):
        m_bIsSelected (false),
        m_bIsPressed (false),
        m_interaction (std::move (interaction))
    {}

    void SetSelected() { m_bIsSelected = true; }
    void SetDeselected() { m_bIsSelected = false; }

    void ExecuteInteracion();

protected:
    bool  m_bIsSelected;
    bool  m_bIsPressed;
    std::unique_ptr <CommandWithContext>  m_interaction;
};
