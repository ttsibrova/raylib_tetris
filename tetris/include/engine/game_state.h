#pragma once

class DrawSettings {
public:
    DrawSettings ():
        m_cellSize (10)
    {}

    int GetCellSize() const { return m_cellSize; }
    void SetCellSize (int cellSize) { m_cellSize = cellSize; }

private:
    int m_cellSize;
};
