#include <core/drawer.h>
#include <core/grid.h>
#include <engine/game.h>
#include <engine/hud.h>
#include <functional/colors.h>
#include <graphics/ui_group_container.h>
#include <raylib/raylib.h>
#include <string>

GridHUD::GridHUD (const Grid* grid, DrawableContainer* ownerContainer):
    m_grid (grid)
{
    m_children.fill (nullptr);
    //m_blockDrawSettings.SetCellSize (20);
}

void GridHUD::FillGraphics()
{
    auto gridBBox = m_grid->GetBoundingBox();
    float width = gridBBox.Max().x - gridBBox.Min().x;
    float height = gridBBox.Max().y - gridBBox.Min().y;
    //Vector2 min {gridBBox.Min().x + 1.2 * width, gridBBox.Min().y};
    //Vector2 max {gridBBox.Max().x + 1.2 * width, gridBBox.Max().y};

    Vector2 min {0, 0};
    Vector2 max {2.2 * width, height};

    auto groupContainer = std::make_unique <UIGroupContainer> (min, max);
    m_graphics->AddDrawableObject ({0., 0.}, DrawPosition::TopLeft, std::move (groupContainer));

    float posXHUDRight = max.x - 0.3 * width;
    float posXHUDLeft = min.x + 0.3 * width;
    float posY = 0.1 * height;
    float posYoffset = 0.18 * height;
    int cellSize = width / 20;

    auto nextBlockDisplay = std::make_unique <NextBlock> (m_graphics.get(), cellSize);
    nextBlockDisplay->SetPosition ({max.x, posY}, DrawPosition::Right);
    m_children[0] = nextBlockDisplay.get();
    m_graphics->AddDrawableObject (std::move (nextBlockDisplay));

    auto scoreDisplay = std::make_unique <Score> (m_graphics.get());
    scoreDisplay->SetPosition ({max.x, posY + posYoffset}, DrawPosition::Right);
    m_children[1] = scoreDisplay.get();
    m_graphics->AddDrawableObject (std::move (scoreDisplay));

    auto holdBlockDisplay = std::make_unique <HoldBlock> (m_graphics.get(), cellSize);
    holdBlockDisplay->SetPosition ({min.x, posY}, DrawPosition::Left);
    m_children[2] = holdBlockDisplay.get();
    m_graphics->AddDrawableObject (std::move (holdBlockDisplay));

    auto linesRemovedDisplay = std::make_unique <NumRemovedLines> (m_graphics.get());
    linesRemovedDisplay->SetPosition ({max.x, posY + posYoffset * 2 }, DrawPosition::Right);
    m_children[3] = linesRemovedDisplay.get();
    m_graphics->AddDrawableObject (std::move (linesRemovedDisplay));

    auto speedLvlDisplay = std::make_unique <SpeedLVL> (m_graphics.get());
    speedLvlDisplay->SetPosition ({max.x, posY + posYoffset * 3 }, DrawPosition::Right);
    m_children[4] = speedLvlDisplay.get();
    m_graphics->AddDrawableObject (std::move (speedLvlDisplay));

    auto comboDisplay = std::make_unique <Combo> (m_graphics.get());
    comboDisplay->SetPosition ({min.x, posY + posYoffset}, DrawPosition::Left);
    m_children[5] = comboDisplay.get();
    m_graphics->AddDrawableObject (std::move (comboDisplay));

}

void GridHUD::Init()
{
    Element::Init();
    for (auto elem : m_children) {
        if (elem) {
            elem->Init();
        }
    }
}

void GridHUD::onNotify (const Object& obj, Event e)
{
    for (auto elem: m_children) {
        if (elem)
            elem->onNotify (obj, e);
    }
}


void GridHUD::DrawLeft (size_t score, char speedLvl, size_t numRemovedLines, const Block* nextBlock) const
{
    //int posXOffset = GetGridOffset() + m_gridWidght + 1;
    //const int tab = 20;
    //DrawRectangle (posXOffset, 0, m_widghtLeft, m_height, Colors::darkBlue);

    //DrawText ("Next block:", posXOffset + tab, 20, 25, Colors::lightBlue);

    //if (nextBlock) {
    //    Drawer::DrawBlock (posXOffset + 40, 60, nextBlock, m_blockDrawSettings);
    //}

    //DrawText ("Score:", posXOffset + tab, 140, 25, Colors::lightBlue);
    //DrawText (std::to_string (score).c_str(), posXOffset + tab, 170, 50, DARKBLUE);

    //DrawText ("Speed level:", posXOffset + tab, 240, 25, Colors::lightBlue);
    //DrawText (std::to_string (speedLvl).c_str(), posXOffset + tab, 270, 50, Colors::green);

    //DrawText ("Lines removed: ", posXOffset + tab, 340, 25, Colors::lightBlue);
    //DrawText (std::to_string (numRemovedLines).c_str(), posXOffset + tab, 370, 50, Colors::purple);
}

void GridHUD::DrawRight (int combo, const Block* holdBlock) const
{
    //const int tab = 20;

    //DrawRectangle (0, 0, m_widghtRight, m_height, Colors::darkBlue);

    //DrawText ("Hold :", tab, 20, 25, Colors::lightBlue);
    //if (holdBlock) {
    //    Drawer::DrawBlock (40, 60, holdBlock, m_blockDrawSettings);
    //}
    //if (combo >= 2) {
    //    DrawText ("Combo : ", tab, 140, 25, Colors::lightBlue);
    //    DrawText (std::to_string (combo).c_str(), 40, 170, 50, YELLOW);
    //}
}

void GridHUD::Score::FillGraphics()
{
    HUDGroup::FillGraphics();

    auto blockBBox = m_graphics->GetBoundingBox();
    float height = blockBBox.Height();
    float width = blockBBox.Width();

    int fontSize = height * 0.45;
    float posScoreY = height * 0.7;
    float offsetX = 0;

    Vector2 minCorner {0, 0};

    m_graphics->AddRectangle ({offsetX, posScoreY}, DrawPosition::Left, fontSize + 3, width, GRAY);
    m_graphics->AddRectangle ({offsetX + 3, posScoreY}, DrawPosition::Left, fontSize - 3, width - 6, BLACK);

    auto scoreText = std::make_unique <shapes::Text> (minCorner, DrawPosition::Right, "0", fontSize);
    scoreText->SetColor (Colors::yellow);
    m_text = scoreText.get();
    m_graphics->AddDrawableObject ({width - offsetX - 8, posScoreY + 2}, DrawPosition::Right, std::move (scoreText));
}


void GridHUD::NumRemovedLines::FillGraphics()
{
    HUDGroup::FillGraphics();

    auto blockBBox = m_graphics->GetBoundingBox();
    float height = blockBBox.Height();
    float width = blockBBox.Width();

    int fontSize = height * 0.45;
    float posScoreY = height * 0.7;
    float offsetX = 0;

    Vector2 minCorner {0, 0};

    m_graphics->AddRectangle ({offsetX, posScoreY}, DrawPosition::Left, fontSize + 3, width, GRAY);
    m_graphics->AddRectangle ({offsetX + 3, posScoreY}, DrawPosition::Left, fontSize - 3, width - 6, BLACK);

    auto linesText = std::make_unique <shapes::Text> (minCorner, DrawPosition::Right, "0", fontSize);
    linesText->SetColor (Colors::green);
    m_text = linesText.get();
    m_graphics->AddDrawableObject ({width - offsetX - 8, posScoreY + 2}, DrawPosition::Right, std::move (linesText));
}

void GridHUD::SpeedLVL::FillGraphics()
{
    HUDGroup::FillGraphics();

    auto blockBBox = m_graphics->GetBoundingBox();
    float height = blockBBox.Height();
    float width = blockBBox.Width();

    int fontSize = height * 0.45;
    float posScoreY = height * 0.7;
    float offsetX = 0;

    Vector2 minCorner {0, 0};

    float fieldWidth = MeasureText ("000", fontSize);
    m_graphics->AddRectangle ({offsetX, posScoreY}, DrawPosition::Left, fontSize + 3, fieldWidth + 6, GRAY);
    auto blackField = m_graphics->AddRectangle ({offsetX + 3, posScoreY}, DrawPosition::Left, fontSize - 3, fieldWidth, BLACK);
    Vector2 textPos = DrawableContainer::ComputePosition (DrawPosition::Right, blackField->GetBoundingBox());

    auto speedText = std::make_unique <shapes::Text> (minCorner, DrawPosition::Right, "1", fontSize);
    speedText->SetColor (Colors::purple);
    m_text = speedText.get();
    m_graphics->AddDrawableObject ({textPos.x - 4, textPos.y + 2}, DrawPosition::Right, std::move (speedText));
}

void GridHUD::Combo::FillGraphics()
{
    HUDGroup::FillGraphics();

    auto blockBBox = m_graphics->GetBoundingBox();
    float height = blockBBox.Height();
    float width = blockBBox.Width();

    int fontSize = height * 0.45;
    float posScoreY = height * 0.7;
    float offsetX = 0;

    Vector2 minCorner {0, 0};

    m_graphics->AddRectangle ({offsetX, posScoreY}, DrawPosition::Left, fontSize + 3, width, GRAY);
    m_graphics->AddRectangle ({offsetX + 3, posScoreY}, DrawPosition::Left, fontSize - 3, width - 6, BLACK);

    auto comboText = std::make_unique <shapes::Text> (minCorner, DrawPosition::Right, "", fontSize);
    comboText->SetColor (Colors::yellow);
    m_text = comboText.get();
    m_graphics->AddDrawableObject ({width - offsetX - 8, posScoreY + 2}, DrawPosition::Right, std::move (comboText));
}

void GridHUD::Score::onNotify (const Object& obj, Event e)
{
    if (e == Event::SCORE_UPDATED) {
        if (auto game = dynamic_cast <const Game*> (&obj)) {
            std::string newText = std::to_string (game->GetScore());
            m_text->UpdateText (newText);
        }
    }
}

void GridHUD::NumRemovedLines::onNotify (const Object& obj, Event e)
{
    if (e == Event::NUM_REMOVED_LINES_UPDATED) {
        if (auto game = dynamic_cast <const Game*> (&obj)) {
            std::string newText = std::to_string (game->GetNumLinesRemoved());
            m_text->UpdateText (newText);
        }
    }
}

void GridHUD::SpeedLVL::onNotify (const Object& obj, Event e)
{
    if (e == Event::SPEED_LVL_UPDATED) {
        if (auto game = dynamic_cast <const Game*> (&obj)) {
            std::string newText = std::to_string (game->GetSpeedLevel());
            m_text->UpdateText (newText);
        }
    }
}

void GridHUD::NextBlock::onNotify (const Object& obj, Event e)
{
    if (e == Event::NEXT_BLOCK_UPDATED) {
        if (auto game = dynamic_cast <const Game*> (&obj)) {
            std::string newText = std::to_string (game->GetScore());
            m_block = game->GetNextBlock();
        }
    }
}
void GridHUD::HoldBlock::onNotify (const Object& obj, Event e)
{
    if (e == Event::HOLD_BLOCK_UPDATED) {
        if (auto game = dynamic_cast <const Game*> (&obj)) {
            std::string newText = std::to_string (game->GetScore());
            m_block = game->GetHoldBlock();
        }
    }
}

void GridHUD::Combo::onNotify (const Object& obj, Event e)
{
    if (e == Event::COMBO_UPDATED) {
        if (auto game = dynamic_cast <const Game*> (&obj)) {

            size_t newCombo = game->GetComboNum();
            if (newCombo == 0) { // combo reset
                m_text->UpdateText ("");
            }
            if (newCombo >= 2) {
                std::string newText = "x " + std::to_string (newCombo);
                m_text->UpdateText (newText);
            }
        }
    }
}

void GridHUD::HUDGroup::FillGraphics()
{
    auto ownerBBox = m_ownerContainer->GetBoundingBox();
    float height = ownerBBox.Height() * 0.14;
    float width = ownerBBox.Width() * 0.24;

    int fontSize = height * 0.3;
    float posStaticTextY = height * 0.2;
    float posScoreY = height * 0.7;
    float offsetX = 0;//width * 0.08;

    Vector2 minCorner{0, 0};
    Vector2 maxCorner{width, height};
    auto groupContainer = std::make_unique <UIGroupContainer> (minCorner, maxCorner);
    //m_graphics->AddRectangle (minCorner, DrawPosition::TopLeft, BoundingBox2d (minCorner, maxCorner), DARKGREEN);
    m_graphics->AddDrawableObject (minCorner, DrawPosition::TopLeft, std::move (groupContainer));
    m_graphics->AddShadedText ({offsetX, posStaticTextY}, DrawPosition::Left, m_HUDGroupName, fontSize, Colors::lightBlue, BLACK);
}

void GridHUD::HUDWithBlock::Draw() const
{
    Element::Draw();
    if (!m_block) {
        return;
    }
    auto bbox = m_graphics->GetBoundingBox();

    auto blockBBox = m_block->GetBBox();
    int blockSizeX = blockBBox.max.m_col - blockBBox.min.m_col + 1;
    int blockSizeY = blockBBox.max.m_row - blockBBox.min.m_row + 1;
    int maxDim = std::max (blockSizeX, blockSizeY);

    float posX = (bbox.Min().x + bbox.Width() / 2) - m_cellSize * (float)maxDim / 2;
    float posY = (bbox.Min().y + bbox.Height() * 0.7) - m_cellSize* (float)maxDim / 2;

    Drawer::DrawBlockShade (posX, posY, m_block, m_cellSize, BLACK);
    Drawer::DrawBlock (posX, posY, m_block, m_cellSize);
}
