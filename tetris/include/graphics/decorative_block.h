#pragma once
#include <core/drawable_object.h>
#include <graphics/drawable_container.h>
#include <core/grid.h>

#include <optional>


class StaticSpite: public IDrawableObject
{
public:
    StaticSpite (DrawPosition align):
        m_graphics (std::make_unique <DrawableContainer>()),
        m_pos{0., 0.},
        m_aligment (align)
    {
    }

    void Init() { // Should be called AFTER SetPosition();
        FillGraphics();
        UpdateLocation();
    }

    void UpdateLocation()
    {
        auto currentAdjPos = DrawableContainer::ComputePosition (m_aligment, GetBoundingBox());
        m_graphics->Translate (DrawableContainer::ComputeTranslation (currentAdjPos, m_pos));
    }

    void SetPosition (const Vector2& pos, DrawPosition align)
    {
        m_pos = pos; m_aligment = align;
    }

    // Should be implemented in exact Sprite
    virtual void FillGraphics() = 0;

    // DrawableObject interface
    virtual void Draw() const override
    {
        m_graphics->Draw();
    }

    virtual BoundingBox2d GetBoundingBox() const override
    {
        return m_graphics->GetBoundingBox();
    }

    virtual void Translate (const Vector2& translation) override
    {
        m_graphics->Translate (translation);
    }

    virtual void Scale (float scale) override {
        m_graphics->Scale (scale);
    }

protected:
    std::unique_ptr <DrawableContainer> m_graphics;
    Vector2            m_pos;

private:
    DrawPosition       m_aligment;
};

class Cell : public StaticSpite
{
public:
    Cell (DrawPosition align, int cellSize, const Color& mainColor, const Color& shadeColor):
        StaticSpite (align),
        m_cellSize (cellSize),
        m_mainColor (mainColor),
        m_internalShadeColor (shadeColor)
    {}

    virtual void FillGraphics() override;

private:
    int   m_cellSize;
    Color m_mainColor;
    Color m_internalShadeColor;
};

class DecorativeBlock: public StaticSpite
{
public:
    DecorativeBlock (DrawPosition align, int cellSize):
        StaticSpite (align),
        m_cellSize (cellSize)
    {}

    void AddCell (const GridPosition& pos, const Color& mainColor, const Color& shadeColor);

    void SetOutline (const Color& outlineColor, int outlineSize);
    void SetExternalShade (const Color& extShadeColor, int extShadeOffset);

    virtual void FillGraphics() override;
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

