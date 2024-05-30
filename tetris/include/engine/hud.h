#pragma once
#include <graphics/ui_element.h>
#include <engine/game_state.h>

class Block;
namespace shapes {
class Text;
}

class GridHUD: public UIElement <CTGSObserver>
{
public:
    class HUDGroup: public UIElement <CTGSObserver>
    {
    public:
        HUDGroup (std::string name, DrawableContainer* ownerContainer):
            m_HUDGroupName (std::move (name)),
            m_ownerContainer (ownerContainer)
        {}
        virtual void FillGraphics() override;
    protected:
        std::string              m_HUDGroupName;
        const DrawableContainer* m_ownerContainer;
    };

    class HUDWithBlock: public HUDGroup
    {
    public:
        HUDWithBlock (std::string HUDGroupName, DrawableContainer* ownerContainer,  int cellSize):
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
        Score (DrawableContainer* ownerContainer):
            HUDGroup ("Score:", ownerContainer)
        {}
        virtual void FillGraphics() override;
        virtual void onNotify (const Object& obj, Event e) override;
    private:
        shapes::Text* m_text;
    };

    class NextBlock: public HUDWithBlock
    {
    public:
        NextBlock (DrawableContainer* ownerContainer, int cellSize):
            HUDWithBlock ("Next block:", ownerContainer, cellSize)
        {}
        virtual void onNotify (const Object& obj, Event e) override;
    };

    class HoldBlock: public HUDWithBlock
    {
    public:
        HoldBlock (DrawableContainer* ownerContainer, int cellSize):
            HUDWithBlock ("Hold:", ownerContainer, cellSize)
        {}
        virtual void onNotify (const Object& obj, Event e) override;
    };

    class SpeedLVL: public HUDGroup
    {
    public:
        SpeedLVL (DrawableContainer* ownerContainer):
            HUDGroup ("Level:", ownerContainer)
        {}
        virtual void FillGraphics() override;
        virtual void onNotify (const Object& obj, Event e) override;

    private:
        shapes::Text* m_text;
    };

    class Combo: public HUDGroup
    {
    public:
        Combo (DrawableContainer* ownerContainer):
            HUDGroup ("Combo:", ownerContainer)
        {}
        virtual void FillGraphics() override;
        virtual void onNotify (const Object& obj, Event e) override;

    private:
        shapes::Text* m_text;
    };

    class NumRemovedLines: public HUDGroup
    {
    public:
        NumRemovedLines (DrawableContainer* ownerContainer):
            HUDGroup ("Line:", ownerContainer)
        {}
        virtual void FillGraphics() override;
        virtual void onNotify (const Object& obj, Event e) override;

    private:
        shapes::Text* m_text;
    };

    GridHUD (const Grid* grid, DrawableContainer* ownerContainer);

    virtual void FillGraphics() override;
    void Init();

    virtual void onNotify (const Object& obj, Event e) override;

    void DrawLeft (size_t Score, char speedLvl, size_t numRemovedLines, const Block* nextBlock) const;
    void DrawRight (int combo, const Block* holdBlock) const;

private:
    const Grid*              m_grid;
    std::array <Element*, 6> m_children;
};
