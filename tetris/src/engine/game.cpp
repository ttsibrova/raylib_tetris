#include <core/drawer.h>
#include <core/blocks.h>
#include <engine/game.h>
#include <graphics/drawable_container.h>
#include <graphics/decorative_block.h>

#include <raylib/raylib.h>
#include <cassert>
#include <cmath>

Game::Game (DrawableContainer* ownerContainer):
    m_drawSettings(),
    m_gameGrid (nullptr),
    m_activeBlock (nullptr),
    m_holdBlock (nullptr),
    m_bCanPlay (false),
    m_bCanHold (true),
    m_speedLvl (1),
    m_gameScore (0),
    m_numRemovedLines(0),
    m_comboNum (0),
    m_ownerContainer (ownerContainer)
{
    m_drawSettings.SetCellSize (40);
}

void Game::Init()
{
    //Graphics registering
    auto grid = std::make_unique <Grid> (m_drawSettings);
    m_gameGrid = grid.get();

    auto ownerBBox = m_ownerContainer->GetBoundingBox();
    Vector2 gridPixelPos {ownerBBox.Min().x + (ownerBBox.Max().x - ownerBBox.Min().x) / 2, ownerBBox.Min().y};

    m_ownerContainer->AddRectangle ({gridPixelPos.x+1, gridPixelPos.y}, DrawPosition::Top, GetGridHeight() + 4, GetGridWidth() + 7, Colors::lightBlue_dimmer);
    m_ownerContainer->AddDrawableObject (gridPixelPos, DrawPosition::Top, std::move (grid));

    auto gameHUD = std::make_unique <GridHUD> (m_gameGrid, m_ownerContainer);
    gameHUD->Init();
    AddObserver (gameHUD.get());
    m_ownerContainer->AddDrawableObject (gridPixelPos, DrawPosition::Top, std::move (gameHUD));

    auto dBlockLeft = std::make_unique <DecorativeBlock> (DrawPosition::BottomLeft, m_drawSettings.GetCellSize());
    dBlockLeft->AddCell ({0, 0}, Colors::yellow, Colors::yellow_shade);
    dBlockLeft->AddCell ({1, 0}, Colors::cyan, Colors::cyan_shade);
    dBlockLeft->AddCell ({2, 0}, Colors::yellow, Colors::yellow_shade);
    dBlockLeft->AddCell ({1, 1}, Colors::cyan, Colors::cyan_shade);
    dBlockLeft->AddCell ({2, 1}, Colors::red, Colors::red_shade);

    m_ownerContainer->AddDrawableObject ({ownerBBox.Min().x, ownerBBox.Max().y}, DrawPosition::BottomLeft, std::move (dBlockLeft));


    m_moveSound = LoadSound ("resources/hi_hat.wav");
    m_fallSound = LoadSound ("resources/snare.wav");
    m_tetrisSound = LoadSound ("resources/ta_da.wav");
    m_holdSound = LoadSound ("resources/808_click.wav");

}

void Game::Start()
{
    m_activeBlock = m_blockFactory.GenerateBlock();
    PrepareBlock (m_activeBlock.get());
    CreateNextBlock();
    m_bCanPlay = true;
    m_bCanHold = true;
}

void Game::Reset()
{
    m_gameGrid->Clear();
    m_gameScore = 0;
    m_comboNum = 0;
    m_bCanPlay = false;
    m_activeBlock = nullptr;
    m_nextBlock = nullptr;
    m_holdBlock = nullptr;
    m_speedLvl = 1;
    m_numRemovedLines = 0;
}

void Game::Draw()
{
    if (m_activeBlock) {
        Drawer::DrawGhostBlock (m_gameGrid->GetPosition().x, m_gameGrid->GetPosition().y, m_ghostBlock.get(), m_drawSettings);
        Drawer::DrawBlock (m_gameGrid->GetPosition().x, m_gameGrid->GetPosition().y, m_activeBlock.get(), m_drawSettings);
    }
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
            RotateBlock();
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

void Game::Tick()
{
    if (CanPlay()) {
        HandleInput();
        UpdateFallingBlock();
    }
}

void Game::MoveBlockDown()
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

void Game::MoveBlockRight()
{
    m_activeBlock->Move (1, 0);
    m_ghostBlock->Move (1, 0);
    if (m_gameGrid->IsOutsideGrid (m_activeBlock->GetBBox())) {
        m_activeBlock->Move (-1, 0);
        m_ghostBlock->Move (-1, 0);
        return;
    }
    if (m_gameGrid->IsCollided (m_activeBlock->GetCurrentCells())) {
        m_activeBlock->Move (-1, 0);
        m_ghostBlock->Move (-1, 0);
        return;
    }
    PlaySound (m_moveSound);
    UpdateGhostBlock();
}

void Game::MoveBlockLeft()
{
    m_activeBlock->Move (-1, 0);
    m_ghostBlock->Move (-1, 0);
    if (m_gameGrid->IsOutsideGrid (m_activeBlock->GetBBox())) {
        m_activeBlock->Move (1, 0);
        m_ghostBlock->Move (1, 0);
        return;
    }
    if (m_gameGrid->IsCollided (m_activeBlock->GetCurrentCells())) {
        m_activeBlock->Move (1, 0);
        m_ghostBlock->Move (1, 0);
        return;
    }
    PlaySound (m_moveSound);
    UpdateGhostBlock();
}

void Game::InstantBlockDrop()
{
    while (!m_gameGrid->IsCollided (m_activeBlock->GetCurrentCells()))
    {
        m_activeBlock->Move (0, 1);
    }
    m_activeBlock->Move (0, -1);
    UpdateElements();
}

void Game::RotateBlock()
{
    m_activeBlock->Rotate();
    m_ghostBlock->Rotate();
    if (m_gameGrid->IsOutsideGrid (m_activeBlock->GetBBox())) {
        m_activeBlock->RotateLeft();
        m_ghostBlock->RotateLeft();
        return;
    }
    if (m_gameGrid->IsCollided (m_activeBlock->GetCurrentCells())) {
        m_activeBlock->RotateLeft();
        m_ghostBlock->RotateLeft();
        return;
    }
    PlaySound (m_moveSound);
    UpdateGhostBlock();
}

void Game::UpdateFallingBlock()
{
    double deltaTime = GetTime() - m_lastFallStarted;
    if (deltaTime > m_baseFallTime / (m_speedLvl * 0.7)) {
        MoveBlockDown();
        m_lastFallStarted = GetTime();
    }
}

int Game::GetGridHeight()
{
    return m_gameGrid->GetGridHeight() * m_drawSettings.GetCellSize();
}

int Game::GetGridWidth()
{
    return m_gameGrid->GetGridWidth() * m_drawSettings.GetCellSize();
}

int Game::GetGameHeight()
{
    return GetGridHeight(); // return height of bbox of graphics container?
}

int Game::GetGameWidth()
{
    return GetGridWidth();// return width of bbox of graphics container?
}

Game::~Game()
{
    UnloadSound (m_moveSound);
    UnloadSound (m_fallSound);
    UnloadSound (m_tetrisSound);
    UnloadSound (m_holdSound);
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
    m_ghostBlock = std::make_unique <Block> (*block);
    m_ghostBlock->SetColorId (8);

    UpdateGhostBlock();
}

void Game::CreateNextBlock()
{
    m_nextBlock = m_blockFactory.GenerateBlock();
    Notify (*this, Event::NEXT_BLOCK_UPDATED);
}

void Game::UpdateElements()
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
    }
    CreateNextBlock();
    m_bCanHold = true;

    PlaySound (m_fallSound);
}

void Game::UpdateScore (int numRemovedLines)
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
        PlaySound (m_tetrisSound);
    }

    if (oldScore != m_gameScore)
        Notify (*this, Event::SCORE_UPDATED);

    if (oldCombo != m_comboNum)
        Notify (*this, Event::COMBO_UPDATED);
}

void Game::HoldBlock()
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
    PlaySound (m_holdSound);
}

void Game::UpdateFallTime()
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

void Game::UpdateGhostBlock()
{
    m_ghostBlock->SetOffset (m_activeBlock->GetOffset());
    while (!m_gameGrid->IsCollided (m_ghostBlock->GetCurrentCells())) {
        m_ghostBlock->Move (0, 1);
    }
    m_ghostBlock->Move (0, -1);
}
