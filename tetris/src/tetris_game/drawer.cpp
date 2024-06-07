#include <tetris_game/drawer.h>

#include <tetris_game/block.h>
#include <graphics/colors.h>
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

void Drawer::DrawGrid (int posX, int posY, const Grid& grid, int cellSize)
{
    DrawRectangle (posX, posY, grid.GetGridWidth() * cellSize + 1 , grid.GetGridHeight() * cellSize + 1, Colors::darkGrey);
    auto mArr = grid.GetRawArr();

    for (size_t i = 0; i < mArr.Dim<0>(); i++) {
        for (size_t j = 0; j < mArr.Dim<1>(); j++) {
            DrawShadedBlock (posX + j * cellSize, posY + i * cellSize, cellSize, mArr.Value (i, j));
        }
    }
}

void Drawer::DrawBlock (int posX, int posY, const Block* block, int cellSize)
{
    const auto& cells = block->GetCurrentCells();
    for (auto& cell : cells) {
        DrawShadedBlock (posX + cell.m_col * cellSize, posY + cell.m_row * cellSize, cellSize, block->GetColorId());
    }
}

void Drawer::DrawGhostBlock (int posX, int posY, const Block* block, int cellSize)
{
        const auto& cells = block->GetCurrentCells ();

        for (auto& cell : cells) {
            DrawRectangle (posX + cell.m_col * cellSize - 2,
                           posY + cell.m_row * cellSize - 2,
                           cellSize + 4,
                           cellSize + 4,
                           Colors::_colors_shade[block->GetColorId()]);
        }
        for (auto& cell : cells) {
            DrawRectangle (posX + cell.m_col * cellSize,
                           posY + cell.m_row * cellSize,
                           cellSize,
                           cellSize,
                           Colors::_colors[block->GetColorId()]);
        }
}

void Drawer::DrawBlockShade (int posX, int posY, const Block* block, int cellSize, const Color& color)
{
    const auto& cells = block->GetCurrentCells();
    for (auto& cell : cells) {
        DrawRectangle (posX + cell.m_col * cellSize + 3,
                       posY + cell.m_row * cellSize + 1,
                       cellSize + 3,
                       cellSize + 3,
                       color);
    }
}
