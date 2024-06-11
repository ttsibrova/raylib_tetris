#include <tetris_game/hud.h>

#include <tetris_game/classic_tetris_game.h>
#include <tetris_game/drawer.h>
#include <tetris_game/grid.h>
#include <graphics/colors.h>
#include <graphics/graphics_helper.h> 
#include <ui/ui_group_container.h>
#include <raylib/raylib.h>
#include <string>

GridHUD::GridHUD (const Grid* grid):
    m_grid (grid)
{
    m_children.fill (nullptr);
    auto gridBBox = m_grid->GetBoundingBox();
    float width = gridBBox.Max().x - gridBBox.Min().x;
    float height = gridBBox.Max().y - gridBBox.Min().y;
    //Vector2 min {gridBBox.Min().x + 1.2 * width, gridBBox.Min().y};
    //Vector2 max {gridBBox.Max().x + 1.2 * width, gridBBox.Max().y};

    Vector2 min{0, 0};
    Vector2 max{2.2 * width, height};

    auto groupContainer = std::make_unique <UIGroupContainer> (min, max);
    m_graphics->AddDrawableObject ({0., 0.}, DrawPosition::TopLeft, std::move (groupContainer));

    float posXHUDRight = max.x - 0.3 * width;
    float posXHUDLeft = min.x + 0.3 * width;
    float posY = 0.1 * height;
    float posYoffset = 0.18 * height;
    int cellSize = width / 20;

    auto nextBlockDisplay = std::make_unique <NextBlock> (m_graphics.get(), cellSize);
    m_children[0] = nextBlockDisplay.get();
    m_graphics->AddDrawableObject ({max.x, posY}, DrawPosition::Right, std::move (nextBlockDisplay));

    auto scoreDisplay = std::make_unique <Score> (m_graphics.get());
    m_children[1] = scoreDisplay.get();
    m_graphics->AddDrawableObject ({max.x, posY + posYoffset}, DrawPosition::Right, std::move (scoreDisplay));

    auto holdBlockDisplay = std::make_unique <HoldBlock> (m_graphics.get(), cellSize);
    m_children[2] = holdBlockDisplay.get();
    m_graphics->AddDrawableObject ({min.x, posY}, DrawPosition::Left, std::move (holdBlockDisplay));

    auto linesRemovedDisplay = std::make_unique <NumRemovedLines> (m_graphics.get());
    m_children[3] = linesRemovedDisplay.get();
    m_graphics->AddDrawableObject ({max.x, posY + posYoffset * 2}, DrawPosition::Right, std::move (linesRemovedDisplay));

    auto speedLvlDisplay = std::make_unique <SpeedLVL> (m_graphics.get());
    m_children[4] = speedLvlDisplay.get();
    m_graphics->AddDrawableObject ({max.x, posY + posYoffset * 3}, DrawPosition::Right, std::move (speedLvlDisplay));

    auto comboDisplay = std::make_unique <Combo> (m_graphics.get());
    m_children[5] = comboDisplay.get();
    m_graphics->AddDrawableObject ({min.x, posY + posYoffset}, DrawPosition::Left, std::move (comboDisplay));
}


void GridHUD::onNotify (const Object& obj, Event e)
{
    for (auto elem: m_children) {
        if (elem)
            elem->onNotify (obj, e);
    }
}


GridHUD::HUDGroup::HUDGroup (std::string name, const DrawableContainer* ownerContainer)
{
    auto ownerBBox = ownerContainer->GetBoundingBox();
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
    m_graphics->AddShadedText ({offsetX, posStaticTextY}, DrawPosition::Left, name, fontSize, Colors::lightBlue, BLACK);
}


GridHUD::Score::Score (const DrawableContainer* ownerContainer):
    HUDGroup ("Score:", ownerContainer)
{
    auto blockBBox = m_graphics->GetBoundingBox();
    float height = blockBBox.Height();
    float width = blockBBox.Width();

    int fontSize = height * 0.45;
    float posScoreY = height * 0.7;
    float offsetX = 0;

    Vector2 minCorner {0, 0};

    m_graphics->AddRectangle ({offsetX, posScoreY}, DrawPosition::Left, fontSize + 3, width, GRAY);
    m_graphics->AddRectangle ({offsetX + 3, posScoreY}, DrawPosition::Left, fontSize - 3, width - 6, BLACK);

    auto scoreText = std::make_unique <shapes::Text> ("0", fontSize);
    scoreText->SetColor (Colors::yellow);
    m_text = scoreText.get();
    m_graphics->AddDrawableObject ({width - offsetX - 8, posScoreY + 2}, DrawPosition::Right, std::move (scoreText));
}

GridHUD::SpeedLVL::SpeedLVL (const DrawableContainer* ownerContainer):
    HUDGroup ("Level:", ownerContainer)
{
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
    Vector2 textPos = GraphicsHelper::ComputePosition (DrawPosition::Right, blackField->GetBoundingBox());

    auto speedText = std::make_unique <shapes::Text> ("1", fontSize);
    speedText->SetColor (Colors::purple);
    m_text = speedText.get();
    m_graphics->AddDrawableObject ({textPos.x - 4, textPos.y + 2}, DrawPosition::Right, std::move (speedText));
}

GridHUD::Combo::Combo (const DrawableContainer* ownerContainer):
    HUDGroup ("Combo:", ownerContainer)
{
    auto blockBBox = m_graphics->GetBoundingBox();
    float height = blockBBox.Height();
    float width = blockBBox.Width();

    int fontSize = height * 0.45;
    float posScoreY = height * 0.7;
    float offsetX = 0;

    Vector2 minCorner {0, 0};

    m_graphics->AddRectangle ({offsetX, posScoreY}, DrawPosition::Left, fontSize + 3, width, GRAY);
    m_graphics->AddRectangle ({offsetX + 3, posScoreY}, DrawPosition::Left, fontSize - 3, width - 6, BLACK);

    auto comboText = std::make_unique <shapes::Text> ("", fontSize);
    comboText->SetColor (Colors::yellow);
    m_text = comboText.get();
    m_graphics->AddDrawableObject ({width - offsetX - 8, posScoreY + 2}, DrawPosition::Right, std::move (comboText));
}


GridHUD::NumRemovedLines::NumRemovedLines (const DrawableContainer* ownerContainer):
    HUDGroup ("Line:", ownerContainer)
{
    auto blockBBox = m_graphics->GetBoundingBox();
    float height = blockBBox.Height();
    float width = blockBBox.Width();

    int fontSize = height * 0.45;
    float posScoreY = height * 0.7;
    float offsetX = 0;

    Vector2 minCorner {0, 0};

    m_graphics->AddRectangle ({offsetX, posScoreY}, DrawPosition::Left, fontSize + 3, width, GRAY);
    m_graphics->AddRectangle ({offsetX + 3, posScoreY}, DrawPosition::Left, fontSize - 3, width - 6, BLACK);

    auto linesText = std::make_unique <shapes::Text> ("0", fontSize);
    linesText->SetColor (Colors::green);
    m_text = linesText.get();
    m_graphics->AddDrawableObject ({width - offsetX - 8, posScoreY + 2}, DrawPosition::Right, std::move (linesText));
}

void GridHUD::Score::onNotify (const Object& obj, Event e)
{
    if (e == Event::SCORE_UPDATED) {
        if (auto game = dynamic_cast <const ClassicTetrisGame*> (&obj)) {
            std::string newText = std::to_string (game->GetScore());
            m_text->UpdateText (newText);
        }
    }
}

void GridHUD::NumRemovedLines::onNotify (const Object& obj, Event e)
{
    if (e == Event::NUM_REMOVED_LINES_UPDATED) {
        if (auto game = dynamic_cast <const ClassicTetrisGame*> (&obj)) {
            std::string newText = std::to_string (game->GetNumLinesRemoved());
            m_text->UpdateText (newText);
        }
    }
}

void GridHUD::SpeedLVL::onNotify (const Object& obj, Event e)
{
    if (e == Event::SPEED_LVL_UPDATED) {
        if (auto game = dynamic_cast <const ClassicTetrisGame*> (&obj)) {
            std::string newText = std::to_string (game->GetSpeedLevel());
            m_text->UpdateText (newText);
        }
    }
}

void GridHUD::NextBlock::onNotify (const Object& obj, Event e)
{
    if (e == Event::NEXT_BLOCK_UPDATED) {
        if (auto game = dynamic_cast <const ClassicTetrisGame*> (&obj)) {
            std::string newText = std::to_string (game->GetScore());
            m_block = game->GetNextBlock();
        }
    }
}
void GridHUD::HoldBlock::onNotify (const Object& obj, Event e)
{
    if (e == Event::HOLD_BLOCK_UPDATED) {
        if (auto game = dynamic_cast <const ClassicTetrisGame*> (&obj)) {
            std::string newText = std::to_string (game->GetScore());
            m_block = game->GetHoldBlock();
        }
    }
}

void GridHUD::Combo::onNotify (const Object& obj, Event e)
{
    if (e == Event::COMBO_UPDATED) {
        if (auto game = dynamic_cast <const ClassicTetrisGame*> (&obj)) {

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
