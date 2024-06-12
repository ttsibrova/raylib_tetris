#pragma once
#include <tetris_game/grid.h>
#include <tetris_game/blocks_factory.h>
#include <tetris_game/hud.h>
#include <engine/game_object.h>
#include <engine/input_handler.h>
#include <engine/settings.h>
#include <engine/command.h>
#include <engine/observer.h>
#include <memory>

class DrawableContainer;

//Commands
class LongPressCommand: public Command
{
public:
    LongPressCommand (float firstDelay, float minDelay):
        m_numConPresses (0),
        m_firstDelay (firstDelay),
        m_minDelay (minDelay),
        m_lastPressTime (0)
    {}
    virtual bool Execute (Object* obj) override;
private:
    int   m_numConPresses;
    float m_firstDelay;
    float m_minDelay; 
    float m_lastPressTime;
};

class CTGMoveLeftCommand: public LongPressCommand
{
public:
    CTGMoveLeftCommand():
        LongPressCommand (0.2f, 0.09f)
    {}

    virtual bool Execute (Object* obj) override;
};

class CTGMoveRightCommand: public LongPressCommand
{
public:
    CTGMoveRightCommand():
        LongPressCommand (0.2f, 0.09f)
    {}
    virtual bool Execute (Object* obj) override;
};

class CTGMoveDownCommand: public LongPressCommand
{
public:
    CTGMoveDownCommand():
        LongPressCommand (0.12f, 0.06f)
    {}
    virtual bool Execute (Object* obj) override;
};

class CTGHoldCommand: public Command
{
public:
    virtual bool Execute (Object* obj) override;
};

class CTGHardDropCommand: public Command
{
public:
    virtual bool Execute (Object* obj) override;
};

class CTGRotateCommand: public Command
{
public:
    virtual bool Execute (Object* obj) override;
};

class CTGPauseCommand: public Command
{
public:
    virtual bool Execute (Object* obj) override;
};


class ClassicTetrisGame : public GameObject, public Subject <CTGSObserver>
{
public:
    ClassicTetrisGame (DrawableContainer* ownerContainer,
                       InputHandler* inputHandler,
                       float scale,
                       const Settings::GamepadMappings& gmap,
                       const Settings::KeyboardMappings& kmap);

    void Init();
    void Start();
    void Reset();
    void Draw();
    bool CanPlay() const { return m_bCanPlay; }
    virtual void Tick() override;

    void MoveBlockDown();
    void MoveBlockRight();
    void MoveBlockLeft();
    void DropBlockHard();
    void RotateBlock();
    void HoldBlock();
    void Pause();
    void Unpause();

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

    ~ClassicTetrisGame();

private:
    void PrepareBlock (Block* block);
    void CreateNextBlock();
    void UpdateElements();
    void UpdateScore (int numRemovedLines);
    void UpdateFallTime();
    void UpdateGhostBlock();
    void UpdateFallingBlock();

private:
    int                          m_cellSize;
    Grid*                        m_gameGrid;
    std::unique_ptr <Block>      m_activeBlock;
    std::unique_ptr <Block>      m_nextBlock;
    std::unique_ptr <Block>      m_holdBlock;
    std::unique_ptr <Block>      m_ghostBlock;
                                 
    bool                         m_bCanPlay;
    bool                         m_bCanHold;
    size_t                       m_gameScore;
    size_t                       m_comboNum;
    size_t                       m_numRemovedLines;
    const double                 m_baseFallTime = 0.85;
    double                       m_lastFallStarted;
    char                         m_speedLvl;
                                 
    BlocksFactory                m_blockFactory;
    InputHandler*                m_inputHandler;
    std::unique_ptr <InputLayer> m_gameInputLayer;
    DrawableContainer*           m_ownerContainer;

    Sound                     m_moveSound;
    Sound                     m_fallSound;
    Sound                     m_tetrisSound;
    Sound                     m_holdSound;
};

