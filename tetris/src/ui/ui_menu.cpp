#include <ui/ui_menu.h>

#include <graphics/graphics_helper.h>


void Menu::AddRow (std::unique_ptr<MenuElement>&& elem1, std::unique_ptr<MenuElement>&& elem2)
{
    float posXe1 = m_columnWidth[0] / 2;
    float posXe2 = m_columnWidth[0] + m_columnWidth[1] / 2;
    float posY = GetNumRows() * m_rowHeight + m_rowHeight / 2;

    if (elem1.get()) {
        auto bbox = elem1->GetBoundingBox();
        auto currentAdjustedPos = GraphicsHelper::ComputePosition (DrawPosition::Center, bbox);
        elem1->SetAlign (DrawPosition::Center);
        elem1->Translate (GraphicsHelper::ComputeTranslation (currentAdjustedPos, {posXe1, posY}));
    }

    if (elem2.get()) {
        auto bbox = elem2->GetBoundingBox();
        auto currentAdjustedPos = GraphicsHelper::ComputePosition (DrawPosition::Center, bbox);
        elem2->SetAlign (DrawPosition::Center);
        elem2->Translate (GraphicsHelper::ComputeTranslation (currentAdjustedPos, {posXe2, posY}));
    }

    m_menuGrid[0].push_back (std::move (elem1));
    m_menuGrid[1].push_back (std::move (elem2));

    if (GetNumRows() == 1) {
        m_menuGrid[m_activeElement[0]][m_activeElement[1]]->SetSelected();
    }
}

void Menu::Select()
{
    m_menuGrid[m_activeElement[0]][m_activeElement[1]]->ExecuteInteracion();
}

void Menu::Exit()
{
    m_exitCommand->ExecuteContext();
}

void Menu::MoveRight()
{
    if (m_activeElement[0] == 0 && IsElementExist (m_activeElement[0] + 1, m_activeElement[1])) {
        m_menuGrid[m_activeElement[0]][m_activeElement[1]]->SetDeselected();
        m_activeElement[0]++;
        m_menuGrid[m_activeElement[0]][m_activeElement[1]]->SetSelected();
    }
}

void Menu::MoveLeft()
{
    if (m_activeElement[0] == 1 && IsElementExist (m_activeElement[0] - 1, m_activeElement[1])) {
        m_menuGrid[m_activeElement[0]][m_activeElement[1]]->SetDeselected();
        m_activeElement[0]--;
        m_menuGrid[m_activeElement[0]][m_activeElement[1]]->SetSelected();
    }
}

void Menu::MoveDown()
{
    if (IsElementExist (m_activeElement[0], m_activeElement[1] + 1)) {
        m_menuGrid[m_activeElement[0]][m_activeElement[1]]->SetDeselected();
        m_activeElement[1]++;
        m_menuGrid[m_activeElement[0]][m_activeElement[1]]->SetSelected();
    }
}

void Menu::MoveUp()
{
    if (IsElementExist (m_activeElement[0], m_activeElement[1] - 1)) {
        m_menuGrid[m_activeElement[0]][m_activeElement[1]]->SetDeselected();
        m_activeElement[1]--;
        m_menuGrid[m_activeElement[0]][m_activeElement[1]]->SetSelected();
    }
}

void Menu::Draw() const
{
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < GetNumRows(); j++) {
            if (m_menuGrid[i][j]) {
                m_menuGrid[i][j]->Draw();
            }
        }
    }
}

BoundingBox2d Menu::GetBoundingBox() const
{
    Vector2 max {m_pos.x + m_columnWidth[0] + m_columnWidth[1], m_pos.y + (float)GetNumRows() * m_rowHeight};
    return {m_pos, max};
}

void Menu::Translate (const Vector2& translation)
{
    m_pos.x += translation.x;
    m_pos.y += translation.y;
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < GetNumRows(); j++) {
            if (m_menuGrid[i][j]) {
                m_menuGrid[i][j]->Translate (translation);
            }
        }
    }
}

void Menu::Scale (float scale)
{
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < GetNumRows(); j++) {
            if (m_menuGrid[i][j]) {
                m_menuGrid[i][j]->Scale (scale);
            }
        }
    }
}

InputLayer Menu::GetStandardMenuInputLayer()
{
    InputLayer inputLayer;

    inputLayer.AddAction (GAMEPAD_BUTTON_LEFT_FACE_DOWN, KEY_ENTER, ActionType::PRESS, std::make_unique <MenuSelectCommand>());
    inputLayer.AddAction (GAMEPAD_BUTTON_RIGHT_FACE_DOWN, KEY_DOWN, ActionType::PRESS, std::make_unique <MenuMoveDownCommand>());
    inputLayer.AddAction (GAMEPAD_BUTTON_RIGHT_FACE_UP, KEY_UP, ActionType::PRESS, std::make_unique <MenuMoveUpCommand>());
    inputLayer.AddAction (GAMEPAD_BUTTON_RIGHT_FACE_LEFT, KEY_LEFT, ActionType::PRESS, std::make_unique <MenuMoveLeftCommand>());
    inputLayer.AddAction (GAMEPAD_BUTTON_RIGHT_FACE_RIGHT, KEY_RIGHT, ActionType::PRESS, std::make_unique <MenuMoveRightCommand>());
    inputLayer.AddAction (GAMEPAD_BUTTON_LEFT_FACE_RIGHT, KEY_ESCAPE, ActionType::PRESS, std::make_unique <MenuExitCommand>());

    return inputLayer;
}

bool Menu::IsElementExist (size_t col, size_t row)
{
    if (col < 2 && row < GetNumRows()) {
        return m_menuGrid[col][row].get();
    }
    return false;
}


bool MenuSelectCommand::Execute (Object* obj)
{
    if (auto menu = dynamic_cast <Menu*> (obj)) {
        menu->Select();
        return true;
    }
    return false;
}

bool MenuExitCommand::Execute (Object* obj)
{
    if (auto menu = dynamic_cast <Menu*> (obj)) {
        menu->Exit();
        return true;
    } 
    return false;
}

bool MenuMoveRightCommand::Execute (Object* obj)
{
    if (auto menu = dynamic_cast <Menu*> (obj)) {
        menu->MoveRight();
        return true;
    }
    return false;
}

bool MenuMoveLeftCommand::Execute (Object* obj)
{
    if (auto menu = dynamic_cast <Menu*> (obj)) {
        menu->MoveLeft();
        return true;
    }
    return false;
}

bool MenuMoveDownCommand::Execute (Object* obj)
{
    if (auto menu = dynamic_cast <Menu*> (obj)) {
        menu->MoveDown();
        return true;
    }
    return false;
}

bool MenuMoveUpCommand::Execute (Object* obj)
{
    if (auto menu = dynamic_cast <Menu*> (obj)) {
        menu->MoveUp();
        return true;
    }
    return false;
}
