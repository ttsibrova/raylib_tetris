#pragma once
#include <core/grid.h>
#include <engine/blocks_factory.h>
#include <engine/game_state.h>
#include <engine/hud.h>
#include <memory>

class Game
{
public:
    Game();

    void Init();
    void Start();
    void Draw();
    void HandleInput();
    bool CanPlay() const { return m_bCanPlay; }

    void MoveBlockDown();
    void MoveBlockRight();
    void MoveBlockLeft();
    void InstantBlockDrop();
    void RotateBlock();
    void UpdateFallingBlock();

    int GetGridHeight();
    int GetGridWidght();
    int GetGameHeight();
    int GetGameWidght();

private:
    void PrepareBlock (Block* block);
    void UpdateElements();
    void UpdateScore (int numRemovedLines);
    void HoldBlock();
    void UpdateFallTime();

private:
    DrawSettings            m_drawSettings;
    Grid                    m_gameGrid;
    std::unique_ptr <Block> m_activeBlock;
    std::unique_ptr <Block> m_nextBlock;
    std::unique_ptr <Block> m_holdBlock;

    bool                    m_bCanPlay;
    bool                    m_bCanHold;
    size_t                  m_gameScore;
    size_t                  m_comboNum;
    size_t                  m_numRemovedLines;
    const double            m_baseFallTime = 1.0;
    double                  m_lastFallStarted;
    char                    m_speedLvl;

    BlocksFactory           m_blockFactory;
    HUD                     m_gameHUD;
};

