#pragma once
#include <graphics/containered_drawable_object.h>
#include <graphics/drawable_container.h>
#include <tetris_game/grid.h>

#include <optional>

class Cell : public ContaineredDrawableObject
{
public:
    Cell (int cellSize, const Color& mainColor, const Color& shadeColor);
};

class DecorativeBlock: public ContaineredDrawableObject
{
public:
    DecorativeBlock (int cellSize):
        m_cellSize (cellSize)
    {}

    void AddCell (const GridPosition& pos, const Color& mainColor, const Color& shadeColor);

    void SetOutline (const Color& outlineColor, int outlineSize);
    void SetExternalShade (const Color& extShadeColor, int extShadeOffset);

    virtual void Draw() const override;
    virtual void Translate (const Vector2& translation) override;

private:
    int                        m_cellSize;
    std::vector <GridPosition> m_positions;
    std::optional <Color>      m_outlineColor;
    int                        m_outlineSize = 2;
    std::optional <Color>      m_externalShadeColor;
    int                        m_extShadeOffset = 3;
};

