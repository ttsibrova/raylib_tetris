#include <engine/game.h>
#include <core/drawer.h>
#include <core/blocks.h>

#include <raylib/raylib.h>
#include <cassert>
#include <cmath>

Game::Game ():
    m_drawSettings (),
    m_gameGrid (),
    m_activeBlock (nullptr),
    m_holdBlock (nullptr),
    m_bCanPlay (true),
    m_bCanHold (true),
    m_speedLvl (1),
    m_gameScore (0),
    m_numRemovedLines(0),
    m_comboNum (0),
    m_gameHUD()
{
    m_drawSettings.SetCellSize (40);
    m_gameHUD.UpdateSizes (GetGridWidght(), GetGridHeight());
}

void Game::Init()
{
    m_gameGrid.Clear();
    m_gameScore = 0;
    m_comboNum = 0;
    m_bCanPlay = false;
    m_activeBlock = nullptr;
    m_nextBlock = nullptr;
    m_holdBlock = nullptr;
    m_speedLvl = 1;
    m_numRemovedLines = 0;
}

void Game::Start()
{
    m_activeBlock = m_blockFactory.GenerateBlock();
    PrepareBlock (m_activeBlock.get());
    m_nextBlock = m_blockFactory.GenerateBlock();
    m_bCanPlay = true;
    m_bCanHold = true;
}

void Game::Draw()
{
    Drawer::DrawGrid (m_gameHUD.GetGridOffset(), 0, m_gameGrid, m_drawSettings);
    if (m_activeBlock) {
        Drawer::DrawBlock (m_gameHUD.GetGridOffset(), 0, m_activeBlock.get(), m_drawSettings);
    }
    m_gameHUD.DrawLeft (m_gameScore, m_speedLvl, m_numRemovedLines, m_nextBlock.get());
    m_gameHUD.DrawRight (m_comboNum, m_holdBlock.get());
}

void Game::HandleInput()
{
    auto keyInput = GetKeyPressed();
    switch (keyInput)
    {
    case KEY_DOWN:
        MoveBlockDown();
        break;
    case KEY_RIGHT:
        MoveBlockRight();
        break;
    case KEY_LEFT:
        MoveBlockLeft();
        break;
    case KEY_R:
        RotateBlock();
        break;
    case KEY_UP:
        InstantBlockDrop();
        break;
    case KEY_E:
        HoldBlock();
        break;
    default:
        break;
    }

    int gamepad = 0;
    if (IsGamepadAvailable (gamepad)) {

        if (IsGamepadButtonPressed (gamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
            RotateBlock ();
        }
        if (IsGamepadButtonPressed (gamepad, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) {
            MoveBlockDown();
        }
        if (IsGamepadButtonPressed (gamepad, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) {
            MoveBlockRight();
        }
        if (IsGamepadButtonPressed (gamepad, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) {
            MoveBlockLeft();
        }
        if (IsGamepadButtonPressed (gamepad, GAMEPAD_BUTTON_LEFT_TRIGGER_1)) {
            HoldBlock();
        }
        if (IsGamepadButtonPressed (gamepad, GAMEPAD_BUTTON_LEFT_FACE_UP)) {
            InstantBlockDrop();
        }
    }

}

void Game::MoveBlockDown()
{
    m_activeBlock->Move (0, 1);
    if (m_gameGrid.IsOutsideGrid (m_activeBlock->GetBBox())) {
        m_activeBlock->Move (0, -1);
        return;
    }
    if (m_gameGrid.IsCollided (m_activeBlock->GetCurrentCells())) {
        m_activeBlock->Move (0, -1);
        UpdateElements();
    }
}

void Game::MoveBlockRight()
{
    m_activeBlock->Move (1, 0);
    if (m_gameGrid.IsOutsideGrid (m_activeBlock->GetBBox())) {
        m_activeBlock->Move (-1, 0);
    }
    if (m_gameGrid.IsCollided (m_activeBlock->GetCurrentCells ())) {
        m_activeBlock->Move (-1, 0);
    }
}

void Game::MoveBlockLeft()
{
    m_activeBlock->Move (-1, 0);
    if (m_gameGrid.IsOutsideGrid (m_activeBlock->GetBBox())) {
        m_activeBlock->Move (1, 0);
    }
    if (m_gameGrid.IsCollided (m_activeBlock->GetCurrentCells ())) {
        m_activeBlock->Move (1, 0);
    }
}

void Game::InstantBlockDrop()
{
    while (!m_gameGrid.IsCollided (m_activeBlock->GetCurrentCells()))
    {
        m_activeBlock->Move (0, 1);
    }
    m_activeBlock->Move (0, -1);
    UpdateElements();
}

void Game::RotateBlock()
{
    m_activeBlock->Rotate();
    if (m_gameGrid.IsOutsideGrid (m_activeBlock->GetBBox())) {
        m_activeBlock->RotateLeft();
        return;
    }
    if (m_gameGrid.IsCollided (m_activeBlock->GetCurrentCells())) {
        m_activeBlock->RotateLeft();
    }
}

void Game::UpdateFallingBlock()
{
    double deltaTime = GetTime() - m_lastFallStarted;
    if (deltaTime > m_baseFallTime / m_speedLvl) {
        MoveBlockDown();
        m_lastFallStarted = GetTime();
    }
}

int Game::GetGridHeight()
{
    return m_gameGrid.GetGridHeight() * m_drawSettings.GetCellSize();
}

int Game::GetGridWidght()
{
    return m_gameGrid.GetGridWidght() * m_drawSettings.GetCellSize();
}

int Game::GetGameHeight()
{
    return GetGridHeight();
}

int Game::GetGameWidght()
{
    return GetGridWidght() + m_gameHUD.GetHUDWidght();
}

void Game::PrepareBlock (Block* block)
{
    switch (block->GetId())
    {
    case 1: block->Move (4, -1); break; //JBlock
    case 2: block->Move (3, -1); break; //IBlock
    default: block->Move (4, 0); break;
    }
    m_lastFallStarted = GetTime();
}

void Game::UpdateElements()
{
    m_gameGrid.AddCells (m_activeBlock->GetCurrentCells(), m_activeBlock->GetColorId());
    int numRemovedLines = m_gameGrid.RemoveRows (m_activeBlock->GetBBox());
    UpdateScore (numRemovedLines);
    m_numRemovedLines += numRemovedLines;
    m_activeBlock.swap (m_nextBlock);
    PrepareBlock (m_activeBlock.get());
    if (m_gameGrid.IsCollided (m_activeBlock->GetCurrentCells())) {
        m_bCanPlay = false;
    }
    m_nextBlock = m_blockFactory.GenerateBlock();
    m_bCanHold = true;
    UpdateFallTime();

}

void Game::UpdateScore (int numRemovedLines)
{
    switch (numRemovedLines)
    {
    case 1:
        m_gameScore += 100 + 50 * m_speedLvl - 1; break;
    case 2:
        m_gameScore += 200 + 75 * m_speedLvl - 1; break;
    case 3:
        m_gameScore += 350 + 120 * m_speedLvl - 1; break;
    case 4:
        m_gameScore += 500 + 200 * m_speedLvl - 1; break;
    default:
        assert (true, "Invalid num of lines.");
        break;
    }
    if (m_comboNum > 0 && numRemovedLines == 0) {
        if (m_comboNum >= 2)
            m_gameScore += 20 * std::pow (2, m_comboNum) + 120 * m_speedLvl - 1;
        m_comboNum = 0;
    } else if (numRemovedLines > 0) {
        m_comboNum++;
    }
}

void Game::HoldBlock()
{
    if (!m_bCanHold || !m_activeBlock) {
        return;
    }
    m_activeBlock.swap (m_holdBlock);
    if (!m_activeBlock) {
        m_activeBlock.swap (m_nextBlock);
        m_nextBlock = m_blockFactory.GenerateBlock();
    }
    PrepareBlock (m_activeBlock.get());
    m_holdBlock->ResetOffset();
    m_bCanHold = false;
}

void Game::UpdateFallTime()
{
    size_t speedLvl = m_numRemovedLines / 25 + 1;
    if (speedLvl > 10) {
        speedLvl = 10;
    }
    m_speedLvl = speedLvl;
}
