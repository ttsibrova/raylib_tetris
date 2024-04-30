#pragma once
#include "functional/settings.h"
#include "functional/tools.h"


class Grid
{
public:

    Grid (int cellHeight, int cellWidght);

    int GetGridHeight () const { return m_cellHeight * Settings::_rowNum; }
    int GetGridWeidght () const { return m_cellWidght * Settings::_colNum; }

    int GetCellHeight () const { return m_cellHeight; }
    int GetCellWidght () const { return m_cellWidght; }

private:
    const int m_cellHeight;
    const int m_cellWidght;

    Tools::multi_array<int, Settings::_colNum, Settings::_rowNum> m_grid;
};
