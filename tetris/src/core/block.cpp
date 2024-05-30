#include <core/block.h>

const std::vector<GridPosition> Block::GetCurrentCells() const
{
    std::vector<GridPosition> updatedPositions;
    for (auto& pos : m_cells[m_rotationState]) {
        updatedPositions.push_back ({pos.m_row + m_offset.m_row, pos.m_col + m_offset.m_col});
    }
    return updatedPositions;
}

GridPositionBBox Block::GetBBox() const
{
    const auto& bbox = m_bboxes[m_rotationState];
    return {{bbox.min.m_row + m_offset.m_row, bbox.min.m_col + m_offset.m_col},
            {bbox.max.m_row + m_offset.m_row, bbox.max.m_col + m_offset.m_col}};
}
