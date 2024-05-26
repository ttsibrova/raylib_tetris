#pragma once
#include <core/bounding_box_2d.h>
#include <engine/game_state.h>
#include <functional/settings.h>
#include <functional/tools.h>

class Grid
{
public:

    using GridType = Tools::multi_array<int, Settings::_rowNum, Settings::_colNum>;

    Grid();


    int GetGridHeight() const { return Settings::_rowNum; }
    int GetGridWidght() const { return Settings::_colNum; }

    bool IsOutsideGrid (const BoundingBox2d& bbox) const;
    bool IsCollided (const std::vector <Position>& cells) const;
    void AddCells (const std::vector <Position>& cells, int colorId);
    int  RemoveRows (const BoundingBox2d& hint);

    void PrintGrid() const { std::cout << m_grid; }

    void SetValue (size_t i, size_t j, int val) { m_grid.Value (i, j) = val; }

    void Clear() { m_grid.Fill (0); }
    const GridType& GetRawArr() const { return m_grid; }

private:
    GridType            m_grid;
};
