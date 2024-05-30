#pragma once
#include <core/grid.h>
#include <array>
#include <vector>


class Block {
public:
    Block (char id, int colorId) :
        m_id (id),
        m_rotationState (0),
        m_colorId (colorId)
    {}

    const std::vector<GridPosition> GetCurrentCells() const;
    GridPositionBBox GetBBox() const;

    char GetId() const { return m_id; }
    int GetColorId() const { return m_colorId; }
    void SetColorId (int colorId) { m_colorId = colorId; };
    void Rotate() { if (m_rotationState + 1 < 4) m_rotationState++; else m_rotationState = 0; }
    void RotateLeft() { if (m_rotationState > 0) m_rotationState--; else m_rotationState = 3; }
    void Move (int colNum, int rowNum) { m_offset.m_col += colNum; m_offset.m_row += rowNum; }
    void ResetOffset() { m_offset.m_col = 0; m_offset.m_row = 0; }
    const GridPosition& GetOffset() const { return m_offset; }
    void SetOffset (const GridPosition& pos) { m_offset = pos; };

protected:
    void SetCells (std::array <std::vector <GridPosition>, 4>&& cells) { m_cells = std::move (cells); }
    void SetBBoxes (std::array <GridPositionBBox, 4>&& bboxes) { m_bboxes = std::move (bboxes); }

private:
    char m_id;

    std::array <std::vector<GridPosition>, 4> m_cells;
    std::array <GridPositionBBox, 4>         m_bboxes;

    char     m_rotationState;
    GridPosition m_offset = {0, 0};

    int      m_colorId;
};
