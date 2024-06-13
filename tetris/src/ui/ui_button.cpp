#include <ui/ui_button.h>

Button::~Button()
{
    if (m_grahicsButton) {
        delete m_grahicsButton;
        m_grahicsButton = nullptr;
    }
    if (m_grahicsPressed) {
        delete m_grahicsPressed;
        m_grahicsPressed = nullptr;
    }
    if (m_grahicsSelected) {
        delete m_grahicsSelected;
        m_grahicsSelected = nullptr;
    }
}

bool Button::IsClicked()
{
    auto mousePos = GetMousePosition();
    return !GetBoundingBox().IsOutside (mousePos);
}

void Button::Draw() const
{
   if (!m_bIsPressed && !m_bIsSelected) {
       m_grahicsButton->Draw();
       return;
   }
   if (m_bIsSelected) {
       m_grahicsSelected->Draw();
       return;
   }
   if (m_bIsPressed) {
       m_grahicsPressed->Draw();
       return;
   }
}

BoundingBox2d Button::GetBoundingBox() const
{
    return m_grahicsButton->GetBoundingBox();
}

void Button::Translate (const Vector2& translation)
{
    m_grahicsButton->Translate (translation);
    m_grahicsPressed->Translate (translation);
    m_grahicsSelected->Translate (translation);
}

void Button::Scale (float scale)
{
    m_grahicsButton->Scale (scale);
    m_grahicsPressed->Scale (scale);
    m_grahicsSelected->Scale (scale);
}
