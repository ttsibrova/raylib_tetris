#pragma once
#include <graphics/drawable_object_with_container.h>
#include <graphics/drawable_container.h>
#include <tetris_game/grid.h>

#include <optional>

class Cell : public DrawableObjectWithContainer
{
public:
    Cell (float cellSize, const Color& mainColor, const Color& shadeColor);
};

class DecorativeBlock: public DrawableObjectWithContainer
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
    virtual void Scale (float scale) override;

private:
    float                      m_cellSize;
    std::vector <GridPosition> m_positions;
    std::optional <Color>      m_outlineColor;
    float                      m_outlineSize = 2.f;
    std::optional <Color>      m_externalShadeColor;
    float                      m_extShadeOffset = 3.f;
};

