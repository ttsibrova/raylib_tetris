#include <ui/ui_menu_element.h>

#include <engine/audio_manager.h>


void MenuElement::ExecuteInteracion()
{
    m_bIsPressed = true;
    m_bIsSelected = false;
    AudioManager::GetInstance().Play ("button_pressed");
    m_interaction->ExecuteContext();
}
