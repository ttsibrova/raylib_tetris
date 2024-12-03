#include <tetris_game/classic_tetris_game.h>

#include <tetris_game/drawer.h>
#include <tetris_game/blocks.h>
#include <engine/audio_manager.h>
#include <graphics/drawable_container.h>
#include <graphics/decorative_block.h>
#include <graphics/sprites.h>

#include <raylib/raylib.h>
#include <cassert>
#include <cmath>

//commands
bool LongPressCommand::Execute (Object* obj)
{
    if (m_numConPresses == 0) {
        m_numConPresses++;
        m_lastPressTime = GetTime();
        return true; // can continue execution 
    }
    if (m_numConPresses > 0) {
        float deltaTime = GetTime() - m_lastPressTime;
        if (deltaTime > m_firstDelay * 2) {
            m_numConPresses = 1;
            m_lastPressTime = GetTime();
            return true; // can continue execution 
        } else {
            float currentDelay = m_firstDelay - 0.02f * (m_numConPresses - 1);
            currentDelay = currentDelay < m_minDelay ? m_minDelay : currentDelay;
            if (deltaTime > currentDelay) {
                m_numConPresses++;
                m_lastPressTime = GetTime();
                return true; // can continue execution
            } else {
                return false; // input recieved too early
            }
        }
    }

    return false;
}

bool CTGMoveLeftCommand::Execute (Object* obj)
{
    if (!LongPressCommand::Execute (obj)) {
        return false;
    }
    if (auto game = dynamic_cast <ClassicTetrisGame*> (obj)) {
        game->MoveBlockLeft();
        return true;
    }
    return false;
}

bool CTGMoveRightCommand::Execute (Object* obj)
{
    if (!LongPressCommand::Execute (obj)) {
        return false;
    }
    if (auto game = dynamic_cast <ClassicTetrisGame*> (obj)) {
        game->MoveBlockRight();
        return true;
    }
    return false;
}

bool CTGMoveDownCommand::Execute (Object* obj)
{
    if (!LongPressCommand::Execute (obj)) {
        return false;
    }
    if (auto game = dynamic_cast <ClassicTetrisGame*> (obj)) {
        game->MoveBlockDown();
        return true;
    }
    return false;
}

bool CTGHoldCommand::Execute (Object* obj)
{
    if (auto game = dynamic_cast <ClassicTetrisGame*> (obj)) {
        game->HoldBlock();
        return true;
    }
    return false;
}

bool CTGHardDropCommand::Execute (Object* obj)
{
    if (auto game = dynamic_cast <ClassicTetrisGame*> (obj)) {
        game->DropBlockHard();
        return true;
    }
    return false;
}

bool CTGRotateCommand::Execute (Object* obj)
{
    if (auto game = dynamic_cast <ClassicTetrisGame*> (obj)) {
        game->RotateBlock();
        return true;
    }
    return false;
}

bool CTGPauseCommand::Execute (Object* obj)
{
    if (auto game = dynamic_cast <ClassicTetrisGame*> (obj)) {
        game->Pause();
        return true;
    }
    return false;
}

ClassicTetrisGame::ClassicTetrisGame (DrawableContainer* ownerContainer,
                                      float scale,
                                      const settings::GamepadMappings& gmap,
                                      const settings::KeyboardMappings& kmap):
    m_cellSize (40 * scale),
    m_gameGrid (nullptr),
    m_activeBlock (nullptr),
    m_holdBlock (nullptr),
    m_bCanPlay (false),
    m_bCanHold (true),
    m_speedLvl (1),
    m_gameScore (0),
    m_numRemovedLines(0),
    m_comboNum (0),
    m_lastFallStarted (0),
    m_ownerContainer (ownerContainer)
{
    m_gameInputLayer = std::make_unique <InputLayer> ();
    m_gameInputLayer->AddAction (gmap.m_HoldButton, kmap.m_HoldKey, ActionType::PRESS, std::make_unique <CTGHoldCommand>());
    m_gameInputLayer->AddAction (gmap.m_HardDropButton, kmap.m_HardDropKey, ActionType::PRESS, std::make_unique <CTGHardDropCommand>());
    m_gameInputLayer->AddAction (gmap.m_RotateButton, kmap.m_RotateKey, ActionType::PRESS, std::make_unique <CTGRotateCommand>());
    m_gameInputLayer->AddAction (GAMEPAD_BUTTON_LEFT_FACE_LEFT, kmap.m_MoveLeftKey, ActionType::HOLD, std::make_unique <CTGMoveLeftCommand>());
    m_gameInputLayer->AddAction (GAMEPAD_BUTTON_LEFT_FACE_RIGHT, kmap.m_MoveRightKey, ActionType::HOLD, std::make_unique <CTGMoveRightCommand>());
    m_gameInputLayer->AddAction (GAMEPAD_BUTTON_LEFT_FACE_DOWN, kmap.m_MoveDown, ActionType::HOLD, std::make_unique <CTGMoveDownCommand>());
    m_gameInputLayer->AddAction (GAMEPAD_BUTTON_MIDDLE_RIGHT, KEY_ESCAPE, ActionType::PRESS, std::make_unique <CTGPauseCommand>());

    InputHandler::GlobalInstance().AddLayer (m_gameInputLayer.get(), this);
}

void ClassicTetrisGame::Init()
{
    //Graphics registering
    m_gameGrid = new Grid (m_cellSize);

    auto ownerBBox = m_ownerContainer->GetBoundingBox();
    Vector2 gridPixelPos {ownerBBox.Min().x + (ownerBBox.Max().x - ownerBBox.Min().x) / 2, ownerBBox.Min().y};

    DrawableContainerTools::AddRectangle (*m_ownerContainer, {gridPixelPos.x+1, gridPixelPos.y}, DrawPosition::Top, GetGridHeight() + 4, GetGridWidth() + 7, Colors::lightBlue_dimmer);
    m_ownerContainer->AddDrawableObject (gridPixelPos, DrawPosition::Top, m_gameGrid);

    auto gameHUD = new GridHUD (m_gameGrid);
    AddObserver (gameHUD);
    m_ownerContainer->AddDrawableObject (gridPixelPos, DrawPosition::Top, gameHUD);

}

void ClassicTetrisGame::Start()
{
    m_activeBlock = m_blockFactory.GenerateBlock();
    PrepareBlock (m_activeBlock.get());
    CreateNextBlock();
    m_bCanPlay = true;
    m_bCanHold = true;
}

void ClassicTetrisGame::Reset()
{
    m_gameGrid->Clear();
    m_gameScore = 0;
    Notify (*this, Event::SCORE_UPDATED);
    m_comboNum = 0;
    Notify (*this, Event::COMBO_UPDATED);
    m_bCanPlay = false;
    m_activeBlock = nullptr;
    m_nextBlock = nullptr;
    Notify (*this, Event::NEXT_BLOCK_UPDATED);
    m_holdBlock = nullptr;
    Notify (*this, Event::HOLD_BLOCK_UPDATED);
    m_speedLvl = 1;
    Notify (*this, Event::SPEED_LVL_UPDATED);
    m_numRemovedLines = 0;
    Notify (*this, Event::NUM_REMOVED_LINES_UPDATED);
}

void ClassicTetrisGame::Draw()
{
    if (m_activeBlock) {
        Drawer::DrawGhostBlock (m_gameGrid->GetPosition().x, m_gameGrid->GetPosition().y, m_ghostBlock.get(), m_cellSize);
        Drawer::DrawBlock (m_gameGrid->GetPosition().x, m_gameGrid->GetPosition().y, m_activeBlock.get(), m_cellSize);
    }
}

void ClassicTetrisGame::Update()
{
    if (CanPlay()) {
        UpdateFallingBlock();
    }
}

void ClassicTetrisGame::MoveBlockDown()
{
    m_activeBlock->Move (0, 1);
    if (m_gameGrid->IsOutsideGrid (m_activeBlock->GetBBox())) {
        m_activeBlock->Move (0, -1);
        return;
    }
    if (m_gameGrid->IsCollided (m_activeBlock->GetCurrentCells())) {
        m_activeBlock->Move (0, -1);
        UpdateElements();
    }
}

void ClassicTetrisGame::MoveBlockRight()
{
    m_activeBlock->Move (1, 0);
    if (m_gameGrid->IsOutsideGrid (m_activeBlock->GetBBox())) {
        m_activeBlock->Move (-1, 0);
        return;
    }
    if (m_gameGrid->IsCollided (m_activeBlock->GetCurrentCells())) {
        m_activeBlock->Move (-1, 0);
        return;
    }
    AudioManager::GetInstance().Play ("block_move");
    UpdateGhostBlock();
}

void ClassicTetrisGame::MoveBlockLeft()
{
    m_activeBlock->Move (-1, 0);
    if (m_gameGrid->IsOutsideGrid (m_activeBlock->GetBBox())) {
        m_activeBlock->Move (1, 0);
        return;
    }
    if (m_gameGrid->IsCollided (m_activeBlock->GetCurrentCells())) {
        m_activeBlock->Move (1, 0);
        return;
    }
    AudioManager::GetInstance().Play ("block_move");
    UpdateGhostBlock();
}

void ClassicTetrisGame::DropBlockHard()
{
    while (!m_gameGrid->IsCollided (m_activeBlock->GetCurrentCells()))
    {
        m_activeBlock->Move (0, 1);
    }
    m_activeBlock->Move (0, -1);
    UpdateElements();
}

void ClassicTetrisGame::RotateBlock()
{
    m_activeBlock->Rotate();
    m_ghostBlock->Rotate();
    if (m_gameGrid->IsOutsideGrid (m_activeBlock->GetBBox())) {

        bool bBordersTest = false;
        if (TestBlock ({0, 1})) {
            bBordersTest = true;
        } else if (TestBlock ({0, -1})) {
            bBordersTest = true;
        } else if (TestBlock ({0, 2})) { // I block rotation case
            bBordersTest = true;
        }

        if (!bBordersTest) {
            m_activeBlock->RotateLeft();
            m_ghostBlock->RotateLeft();
            return;
        }
    }
    if (m_gameGrid->IsCollided (m_activeBlock->GetCurrentCells())) {
        m_activeBlock->RotateLeft();
        m_ghostBlock->RotateLeft();
        return;
    }
    AudioManager::GetInstance().Play ("block_move");
    UpdateGhostBlock();
}

void ClassicTetrisGame::UpdateFallingBlock()
{
    double deltaTime = GetTime() - m_lastFallStarted;
    if (deltaTime > m_baseFallTime / (m_speedLvl * 0.7)) {
        MoveBlockDown();
        m_lastFallStarted = GetTime();
    }
}

bool ClassicTetrisGame::TestBlock (const GridPosition& offset)
{
    m_activeBlock->Move (offset.m_col, offset.m_row);
    if (m_gameGrid->IsOutsideGrid (m_activeBlock->GetBBox())) {
        m_activeBlock->Move (-offset.m_col, -offset.m_row);
        return false;
    }
    return true;
}

int ClassicTetrisGame::GetGridHeight()
{
    return m_gameGrid->GetGridHeight() * m_cellSize;
}

int ClassicTetrisGame::GetGridWidth()
{
    return m_gameGrid->GetGridWidth() * m_cellSize;
}

int ClassicTetrisGame::GetGameHeight()
{
    return GetGridHeight(); // return height of bbox of graphics container?
}

int ClassicTetrisGame::GetGameWidth()
{
    return GetGridWidth();// return width of bbox of graphics container?
}

ClassicTetrisGame::~ClassicTetrisGame()
{
    InputHandler::GlobalInstance().ReleaseLayer();
}

void ClassicTetrisGame::PrepareBlock (Block* block)
{
    switch (block->GetId())
    {
    case 1: block->Move (4, -1); break; //JBlock
    case 2: block->Move (3, -1); break; //IBlock
    default: block->Move (4, 0); break;
    }
    m_lastFallStarted = GetTime();
    m_ghostBlock = std::make_unique <Block> (*block);
    m_ghostBlock->SetColorId (8);

    UpdateGhostBlock();
}

void ClassicTetrisGame::CreateNextBlock()
{
    m_nextBlock = m_blockFactory.GenerateBlock();
    Notify (*this, Event::NEXT_BLOCK_UPDATED);
}

void ClassicTetrisGame::UpdateElements()
{
    m_gameGrid->AddCells (m_activeBlock->GetCurrentCells(), m_activeBlock->GetColorId());
    int numRemovedLines = m_gameGrid->RemoveRows (m_activeBlock->GetBBox());
    UpdateScore (numRemovedLines);
    m_numRemovedLines += numRemovedLines;
    if (numRemovedLines > 0) {
        Notify (*this, Event::NUM_REMOVED_LINES_UPDATED);
        UpdateFallTime();
    }
    m_activeBlock.swap (m_nextBlock);
    PrepareBlock (m_activeBlock.get());
    if (m_gameGrid->IsCollided (m_activeBlock->GetCurrentCells())) {
        m_bCanPlay = false;
        Notify (*this, Event::GAME_OVER);
    }
    CreateNextBlock();
    m_bCanHold = true;

    AudioManager::GetInstance().Play ("block_drop");
}

void ClassicTetrisGame::UpdateScore (int numRemovedLines)
{
    size_t oldScore = m_gameScore;
    size_t oldCombo = m_comboNum;
    switch (numRemovedLines)
    {
    case 1:
        m_gameScore += 100 + 50 * (m_speedLvl - 1); break;
    case 2:
        m_gameScore += 200 + 75 * (m_speedLvl - 1); break;
    case 3:
        m_gameScore += 350 + 120 * (m_speedLvl - 1); break;
    case 4:
        m_gameScore += 500 + 200 * (m_speedLvl - 1); break;
    default:
        assert (true, "Invalid num of lines.");
        break;
    }
    if (m_comboNum > 0 && numRemovedLines == 0) {
        if (m_comboNum >= 2)
            m_gameScore += 20 * std::pow (2, m_comboNum) + 120 * (m_speedLvl - 1);
        m_comboNum = 0;
    } else if (numRemovedLines > 0) {
        m_comboNum++;
    }
    if (numRemovedLines == 4) {
        AudioManager::GetInstance().Play ("tetris");
    }

    if (oldScore != m_gameScore)
        Notify (*this, Event::SCORE_UPDATED);

    if (oldCombo != m_comboNum)
        Notify (*this, Event::COMBO_UPDATED);
}

void ClassicTetrisGame::HoldBlock()
{
    if (!m_bCanHold || !m_activeBlock) {
        return;
    }
    m_activeBlock.swap (m_holdBlock);
    if (!m_activeBlock) {
        m_activeBlock.swap (m_nextBlock);
        CreateNextBlock();
    }
    PrepareBlock (m_activeBlock.get());
    m_holdBlock->ResetOffset();
    m_bCanHold = false;
    Notify (*this, Event::HOLD_BLOCK_UPDATED);
    AudioManager::GetInstance().Play ("block_hold");
}

void ClassicTetrisGame::Pause()
{
    m_bCanPlay = false;
    Notify (*this, Event::PAUSE);
}

void ClassicTetrisGame::Unpause()
{
    m_bCanPlay = true;
}

void ClassicTetrisGame::UpdateFallTime()
{
    size_t speedLvl = m_numRemovedLines / 15 + 1;
    if (speedLvl > 10) {
        speedLvl = 10;
    }
    if (m_speedLvl != speedLvl) {
        m_speedLvl = speedLvl;
        Notify (*this, Event::SPEED_LVL_UPDATED);
    }
}

void ClassicTetrisGame::UpdateGhostBlock()
{
    m_ghostBlock->SetOffset (m_activeBlock->GetOffset());
    while (!m_gameGrid->IsCollided (m_ghostBlock->GetCurrentCells())) {
        m_ghostBlock->Move (0, 1);
    }
    m_ghostBlock->Move (0, -1);
}

