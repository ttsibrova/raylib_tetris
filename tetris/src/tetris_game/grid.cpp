#include <tetris_game/grid.h>

#include <tetris_game/drawer.h>
#include <graphics/drawable_container.h>
#include <cassert>
#include <unordered_set>

Grid::Grid (int cellSize):
    m_pos {0., 0.},
    m_grid (0),
    m_cellSize (cellSize)
{}

bool Grid::IsOutsideGrid (const GridPositionBBox& bbox) const
{
    if (bbox.min.m_col < 0 || bbox.max.m_col > GetGridWidth() - 1) {
        return true;
    }
    return false;
}

bool Grid::IsCollided (const std::vector<GridPosition>& cells) const
{
    for (auto& cell : cells) {
        if (cell.m_row > GetGridHeight() - 1) {
            return true;
        }
        if (cell.m_row >= 0 && cell.m_col >= 0 && m_grid.Value (cell.m_row, cell.m_col) != 0) {
            return true;
        }
    }
    return false;
}

void Grid::AddCells (const std::vector<GridPosition>& cells, int colorId)
{
    for (auto& cell : cells) {
        m_grid.Value (cell.m_row, cell.m_col) = colorId;
    }
}

int Grid::RemoveRows (const GridPositionBBox& hint)
{
    std::unordered_set <size_t> linesToRemove;
    for (size_t i = hint.min.m_row; i <= hint.max.m_row; i++) {
        bool bIsFull = true;
        for (size_t j = 0; j < m_grid.Dim<1>(); j++) {
            if (m_grid.Value (i, j) == 0) {
                bIsFull = false;
                break;
            }
        }
        if (bIsFull) {
            linesToRemove.insert (i);
        }
    }
    if (linesToRemove.empty()) {
        return 0;
    }

#if _DEBUG
    std::cout << "Grid state before removal\n";
    PrintGrid();
    int filledLinesBefore = 0;
    for (size_t i = 0; i < m_grid.Dim<0>(); i++) {
        bool bIsNotEmpty = false;
        for (size_t j = 0; j < m_grid.Dim<1>(); j++) {
            if (m_grid.Value (i, j) != 0) {
                bIsNotEmpty = true;
                break;
            }
        }
        if (bIsNotEmpty) {
            filledLinesBefore++;
        }
    }
    std::cout << "Filled lines before removal :" << filledLinesBefore << std::endl;
#endif

    int fillIdx = m_grid.Dim<0>() - 1;
    bool bUseDummy = false;
    for (int i = m_grid.Dim<0>() - 1; i >= 0; i--) {
        if (!bUseDummy && linesToRemove.contains (fillIdx)) {
            while (linesToRemove.contains (fillIdx))
            {
                fillIdx--;
                if (fillIdx < 0) {
                    bUseDummy = true;
                    break;
                }
            }
        }
        for (int j = 0; j < m_grid.Dim<1>(); j++) {
            if (!bUseDummy)
                m_grid.Value (i, j) = m_grid.Value (fillIdx, j);
            else
                m_grid.Value (i, j) = 0;
        }
        if (fillIdx <= 0 && i > 0) {
            bUseDummy = true;
        }
        fillIdx--;
    }
#if _DEBUG
    int filledLinesAfter = 0;
    for (size_t i = 0; i < m_grid.Dim<0> (); i++) {
        bool bIsNotEmpty = false;
        for (size_t j = 0; j < m_grid.Dim<1> (); j++) {
            if (m_grid.Value (i, j) != 0) {
                bIsNotEmpty = true;
                break;
            }
        }
        if (bIsNotEmpty) {
            filledLinesAfter++;
        }
    }
    std::cout << "Supposed to remove " << linesToRemove.size() << " lines" << std::endl;
    std::cout << "In fact removed :" << filledLinesBefore - filledLinesAfter << std::endl;
    if (filledLinesBefore - filledLinesAfter == linesToRemove.size()) {
        std::cout << "CORRECT\n";
    }
    else {
        std::cout << "FAIL REMOVAL\n";
    }
    PrintGrid ();
    std::cout << std::endl;
#endif
    return linesToRemove.size();
}

void Grid::Draw() const
{
    Drawer::DrawGrid (m_pos.x, m_pos.y, *this, m_cellSize);
}

BoundingBox2d Grid::GetBoundingBox() const
{
    return {m_pos, {m_pos.x + GetGridWidth() * m_cellSize, m_pos.y + GetGridHeight() * m_cellSize}};
}

void Grid::Translate (const Vector2& translation)
{
    m_pos.x += translation.x;
    m_pos.y += translation.y;
}

void Grid::Scale (float scale)
{

}


