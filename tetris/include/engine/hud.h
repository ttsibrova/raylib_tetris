#pragma once
#include <engine/game_state.h>

class Block;

class HUD
{
public:
    HUD();

    void UpdateSizes (int gridWidght, int gridHeight);

    void DrawLeft (size_t Score, char speedLvl, size_t numRemovedLines, const Block* nextBlock) const;
    void DrawRight (int combo, const Block* holdBlock) const;
    int GetHUDWidght() const { return m_widghtRight + m_widghtLeft; }
    int GetHUDHeight() const { return m_height; }

    int GetGridOffset() const { return m_widghtRight + 1; }

private:
    int          m_widghtRight;
    int          m_widghtLeft;
    int          m_height;

    int          m_gridWidght;
    DrawSettings m_blockDrawSettings;
};
