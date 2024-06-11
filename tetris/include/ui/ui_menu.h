#pragma once
#include <engine/game_object.h>
#include <ui/ui_menu_element.h>

#include <array>
#include <vector>


class MenuSelectCommand: public Command
{
public:
    virtual bool Execute (Object* obj) override;
};

class MenuExitCommand: public Command
{
public:
    virtual bool Execute (Object* obj) override;
};

class MenuMoveRightCommand: public Command
{
public:
    virtual bool Execute (Object* obj) override;
};

class MenuMoveLeftCommand: public Command
{
public:
    virtual bool Execute (Object* obj) override;
};

class MenuMoveDownCommand: public Command
{
public:
    virtual bool Execute (Object* obj) override;
};

class MenuMoveUpCommand: public Command
{
public:
    virtual bool Execute (Object* obj) override;
};

class Menu: public DrawableObject
{
public:
    Menu (float rowHeight, std::unique_ptr <CommandWithContext>&& exitCommand):
        m_rowHeight (rowHeight),
        m_exitCommand (std::move (exitCommand))
    {}

    //Can and will return nullptr
    //MenuElement* GetElement (size_t col, size_t row) const;
    //std::pair <MenuElement*, MenuElement*> GetRow (size_t row) const { return {m_menuGrid[0][row], m_menuGrid[1][row]}; }
    void AddRow (std::unique_ptr <MenuElement>&& elem1, std::unique_ptr <MenuElement>&& elem2 = nullptr);
    void SetColumnWidth (float col1, float col2 = 0.f)         { m_columnWidth[0] = col1; m_columnWidth[1] = col2; };
    size_t GetNumRows() const                                  { return m_menuGrid[0].size(); }

    //void HandleMouseMoved();
    void Select();
    void Exit();
    void MoveRight();
    void MoveLeft();
    void MoveDown();
    void MoveUp();

    virtual void Draw() const override;
    virtual BoundingBox2d GetBoundingBox() const override;
    virtual void Translate (const Vector2& translation) override;
    virtual void Scale (float scale) override;

private:
    bool IsElementExist (size_t col, size_t row);

private:
    float m_columnWidth[2] = {0.f, 0.f};
    float m_rowHeight = 0;
    size_t m_activeElement[2] = {0, 0};
    std::unique_ptr <CommandWithContext>       m_exitCommand;
    std::array <std::vector <std::unique_ptr <MenuElement>>, 2> m_menuGrid;
};
