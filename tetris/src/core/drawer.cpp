#include <core/drawer.h>

#include <core/block.h>
#include <engine/game_state.h>
#include <functional/colors.h>
#include <raylib/raylib.h>

namespace {
    void DrawShadedBlock (int posX, int posY, int cellSize, int colorId)
    {
        int shadeSize = cellSize / 10;
        DrawRectangle (posX + 1,
                       posY + 1,
                       cellSize - 1,
                       cellSize - 1,
                       Colors::_colors_shade[colorId]);
        DrawRectangle (posX + shadeSize + 1,
                       posY + shadeSize + 1,
                       cellSize - shadeSize * 2 - 2,
                       cellSize - shadeSize * 2 - 2,
                       Colors::_colors[colorId]);
    }
}

void Drawer::DrawGrid (int posX, int posY, const Grid& grid, const DrawSettings& state)
{
    auto mArr = grid.GetRawArr();

    for (size_t i = 0; i < mArr.Dim<0>(); i++) {
        for (size_t j = 0; j < mArr.Dim<1>(); j++) {
            DrawShadedBlock (posX + j * state.GetCellSize(), posY + i * state.GetCellSize(), state.GetCellSize(), mArr.Value (i, j));
        }
    }
}

void Drawer::DrawBlock (int posX, int posY, const Block* block, const DrawSettings& settings)
{
    auto cellSize = settings.GetCellSize();
    const auto& cells = block->GetCurrentCells();
    for (auto& cell : cells) {
        DrawShadedBlock (posX + cell.m_col * cellSize, posY + cell.m_row * cellSize, cellSize, block->GetColorId());
    }
}
