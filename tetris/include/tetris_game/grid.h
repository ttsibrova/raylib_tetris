#pragma once
#include <core/bounding_box_2d.h>
#include <core/tools.h>
#include <graphics/drawable_object.h>

#include <vector>

class DrawableContainer;

struct GridPosition
{
    int m_row = 0;
    int m_col = 0;
};

struct GridPositionBBox
{
    GridPosition min;
    GridPosition max;
};

class Grid : public DrawableObject
{
public:

    using GridType = Tools::multi_array<int, 20, 10>;

    Grid (int cellSize);


    int GetGridHeight() const { return m_grid.Dim<0>(); }
    int GetGridWidth() const { return  m_grid.Dim<1>(); }

    bool IsOutsideGrid (const GridPositionBBox& bbox) const;
    bool IsCollided (const std::vector <GridPosition>& cells) const;
    void AddCells (const std::vector <GridPosition>& cells, int colorId);
    int  RemoveRows (const GridPositionBBox& hint);

    void PrintGrid() const { std::cout << m_grid; }

    void SetValue (size_t i, size_t j, int val) { m_grid.Value (i, j) = val; }

    void Clear() { m_grid.Fill (0); }
    const GridType& GetRawArr() const { return m_grid; }

    //Drawable Object Interface
    virtual void Draw() const override;
    virtual BoundingBox2d GetBoundingBox() const override;
    virtual void Translate (const Vector2& translation) override;
    virtual void Scale (float scale) override;

    const Vector2& GetPosition() { return m_pos; }

private:
    Vector2  m_pos;
    GridType m_grid;
    int      m_cellSize;
};
