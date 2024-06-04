#pragma once
#include <core/grid.h>
#include <engine/blocks_factory.h>
#include <engine/game_object.h>
#include <engine/game_state.h>
#include <engine/hud.h>
#include <functional/observer.h>
#include <memory>

class DrawableContainer;

class Game : public Object, public Subject <CTGSObserver>
{
public:
    Game (DrawableContainer* ownerContainer);

    void Init();
    void Start();
    void Reset();
    void Draw();
    void HandleInput();
    bool CanPlay() const { return m_bCanPlay; }
    virtual void Tick() override;

    void MoveBlockDown();
    void MoveBlockRight();
    void MoveBlockLeft();
    void InstantBlockDrop();
    void RotateBlock();
    void UpdateFallingBlock();

    int GetGridHeight();
    int GetGridWidth();
    int GetGameHeight();
    int GetGameWidth();

    //States returns
    size_t GetScore() const {return m_gameScore;}
    size_t GetComboNum() const {return m_comboNum;}
    size_t GetNumLinesRemoved() const {return m_numRemovedLines;}
    char   GetSpeedLevel() const {return m_speedLvl;}
    const Block* GetNextBlock() const {return m_nextBlock.get();}
    const Block* GetHoldBlock() const {return m_holdBlock.get();}

    ~Game();

private:
    void PrepareBlock (Block* block);
    void CreateNextBlock();
    void UpdateElements();
    void UpdateScore (int numRemovedLines);
    void HoldBlock();
    void UpdateFallTime();
    void UpdateGhostBlock();

private:
    DrawSettings              m_drawSettings;
    Grid*                     m_gameGrid;
    std::unique_ptr <Block>   m_activeBlock;
    std::unique_ptr <Block>   m_nextBlock;
    std::unique_ptr <Block>   m_holdBlock;
    std::unique_ptr <Block>   m_ghostBlock;

    bool                      m_bCanPlay;
    bool                      m_bCanHold;
    size_t                    m_gameScore;
    size_t                    m_comboNum;
    size_t                    m_numRemovedLines;
    const double              m_baseFallTime = 0.85;
    double                    m_lastFallStarted;
    char                      m_speedLvl;

    BlocksFactory             m_blockFactory;
    //std::unique_ptr <GridHUD> m_gameHUD;
    DrawableContainer*        m_ownerContainer;

    Sound                     m_moveSound;
    Sound                     m_fallSound;
    Sound                     m_tetrisSound;
    Sound                     m_holdSound;
};

