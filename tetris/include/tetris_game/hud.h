#pragma once
#include <ui/ui_element.h>
#include <array>

class Block;
class Grid;
namespace shapes {
class Text;
}

class GridHUD: public UIElement <CTGSObserver>
{
public:
    class HUDGroup: public UIElement <CTGSObserver>
    {
    public:
        HUDGroup (std::string name, const DrawableContainer* ownerContainer);
    };

    class HUDWithBlock: public HUDGroup
    {
    public:
        HUDWithBlock (std::string HUDGroupName, const DrawableContainer* ownerContainer,  int cellSize):
            HUDGroup (HUDGroupName, ownerContainer),
            m_cellSize (cellSize),
            m_block (nullptr)
        {}
        virtual void Draw() const override;
    protected:
        int          m_cellSize;
        const Block* m_block;
    };

    class Score: public HUDGroup
    {
    public:
        Score (const DrawableContainer* ownerContainer);
        virtual void onNotify (const Object& obj, Event e) override;
    private:
        shapes::Text* m_text;
    };

    class NextBlock: public HUDWithBlock
    {
    public:
        NextBlock (const DrawableContainer* ownerContainer, int cellSize):
            HUDWithBlock ("Next:", ownerContainer, cellSize)
        {}
        virtual void onNotify (const Object& obj, Event e) override;
    };

    class HoldBlock: public HUDWithBlock
    {
    public:
        HoldBlock (const DrawableContainer* ownerContainer, int cellSize):
            HUDWithBlock ("Hold:", ownerContainer, cellSize)
        {}
        virtual void onNotify (const Object& obj, Event e) override;
    };

    class SpeedLVL: public HUDGroup
    {
    public:
        SpeedLVL (const DrawableContainer* ownerContainer);
        virtual void onNotify (const Object& obj, Event e) override;

    private:
        shapes::Text* m_text;
    };

    class Combo: public HUDGroup
    {
    public:
        Combo (const DrawableContainer* ownerContainer);
        virtual void onNotify (const Object& obj, Event e) override;

    private:
        shapes::Text* m_text;
    };

    class NumRemovedLines: public HUDGroup
    {
    public:
        NumRemovedLines (const DrawableContainer* ownerContainer);
        virtual void onNotify (const Object& obj, Event e) override;

    private:
        shapes::Text* m_text;
    };

    GridHUD (const Grid* grid);

    virtual void onNotify (const Object& obj, Event e) override;

private:
    const Grid*              m_grid;
    std::array <Element*, 6> m_children;
};
