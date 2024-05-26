#include <core/drawer.h>
#include <engine/hud.h>
#include <functional/colors.h>
#include <raylib/raylib.h>
#include <string>

HUD::HUD ():
    m_widghtLeft (100),
    m_widghtRight (100),
    m_height (200),
    m_gridWidght (0)
{
    m_blockDrawSettings.SetCellSize (20);
}

void HUD::UpdateSizes (int gridWidght, int gridHeight)
{
    m_widghtLeft = gridWidght * 0.6;
    m_widghtRight = gridWidght * 0.6;
    m_height = gridHeight;
    m_gridWidght = gridWidght;
}

void HUD::DrawLeft (size_t score, char speedLvl, size_t numRemovedLines, const Block* nextBlock) const
{
    int posXOffset = GetGridOffset () + m_gridWidght + 1;
    const int tab = 20;
    DrawRectangle (posXOffset, 0, m_widghtLeft, m_height, Colors::darkBlue);

    DrawText ("Next block:", posXOffset + tab, 20, 25, Colors::lightBlue);

    if (nextBlock) {
        Drawer::DrawBlock (posXOffset + 40, 60, nextBlock, m_blockDrawSettings);
    }

    DrawText ("Score:", posXOffset + tab, 140, 25, Colors::lightBlue);
    DrawText (std::to_string (score).c_str(), posXOffset + tab, 170, 50, DARKBLUE);

    DrawText ("Speed level:", posXOffset + tab, 240, 25, Colors::lightBlue);
    DrawText (std::to_string (speedLvl).c_str(), posXOffset + tab, 270, 50, Colors::green);

    DrawText ("Lines removed: ", posXOffset + tab, 340, 25, Colors::lightBlue);
    DrawText (std::to_string (numRemovedLines).c_str(), posXOffset + tab, 370, 50, Colors::purple);
}

void HUD::DrawRight (int combo, const Block* holdBlock) const
{
    const int tab = 20;

    DrawRectangle (0, 0, m_widghtRight, m_height, Colors::darkBlue);

    DrawText ("Hold :", tab, 20, 25, Colors::lightBlue);
    if (holdBlock) {
        Drawer::DrawBlock (40, 60, holdBlock, m_blockDrawSettings);
    }
    if (combo >= 2) {
        DrawText ("Combo : ", tab, 140, 25, Colors::lightBlue);
        DrawText (std::to_string (combo).c_str (), 40, 170, 50, YELLOW);
    }
}
