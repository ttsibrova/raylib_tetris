#include <engine/screen.h>
#include <graphics/colors.h>
#include <graphics/decorative_block.h>
#include <graphics/graphics_helper.h>
#include <graphics/sprites.h>
#include <ui/ui_menu.h>
#include <ui/ui_button.h>


MainMenuScreen::MainMenuScreen (InputHandler* iHandler, const ScreenSize& screenSize):
    Screen (iHandler)
{
    float height = screenSize.m_height * screenSize.m_scale;
    float width = screenSize.m_width * screenSize.m_scale;
    m_screenGraphics.AddRectangle ({0.f, 0.f}, DrawPosition::TopLeft, height, width, Colors::darkBlue);

    int cellSize =35 * screenSize.m_scale;
    auto logoContainer = new DrawableContainer();

    auto AddLetter = [cellSize] (DrawableContainer* cont, DrawableObject* letter) {
        auto bbox = cont->GetBoundingBox();
        Vector2 prevPos = GraphicsHelper::ComputePosition (DrawPosition::TopRight, bbox);
        cont->AddDrawableObject ({prevPos.x + cellSize/2, prevPos.y}, DrawPosition::TopLeft, letter);
    };

    auto blueT = SpriteGraphicGenerator::GetBlockLetterT (cellSize, Colors::blue, Colors::blue_shade);
    AddLetter (logoContainer, blueT);

    auto yellowE = SpriteGraphicGenerator::GetBlockLetterE (cellSize, Colors::yellow, Colors::yellow_shade);
    AddLetter (logoContainer, yellowE);

    auto greenT = SpriteGraphicGenerator::GetBlockLetterT (cellSize, Colors::green, Colors::green_shade);
    AddLetter (logoContainer, greenT);

    auto redR = SpriteGraphicGenerator::GetBlockLetterR (cellSize, Colors::red, Colors::red_shade);
    AddLetter (logoContainer, redR);

    auto cyanI = SpriteGraphicGenerator::GetBlockLetterI (cellSize, Colors::cyan, Colors::cyan_shade);
    AddLetter (logoContainer, cyanI);

    auto purpleS = SpriteGraphicGenerator::GetBlockLetterS (cellSize, Colors::purple, Colors::purple_shade);
    AddLetter (logoContainer, purpleS);

    auto screenBBox = m_screenGraphics.GetBoundingBox();
    Vector2 topCenter = GraphicsHelper::ComputePosition (DrawPosition::Top, screenBBox);

    Vector2 logoPos {topCenter.x, topCenter.y + height * 0.15};
    m_screenGraphics.AddDrawableObject (logoPos, DrawPosition::Top, logoContainer);

    auto block1 = SpriteGraphicGenerator::GetMenuDecorativeBlock (cellSize);
    float posX = block1->GetBoundingBox().Width() + 1;
    m_screenGraphics.AddDrawableObject ({0, height}, DrawPosition::BottomLeft, block1);
    auto block2 = SpriteGraphicGenerator::GetMenuDecorativeBlockInversed (cellSize);
    if (auto bl = dynamic_cast <DecorativeBlock*> (block2)) {
        bl->AddCell ({3,0}, Colors::purple, Colors::purple_shade);
    }
    m_screenGraphics.AddDrawableObject ({posX, height + (cellSize + 1) * 2}, DrawPosition::BottomLeft, block2);
    auto block3 = SpriteGraphicGenerator::GetMenuDecorativeBlockInversed (cellSize);
    m_screenGraphics.AddDrawableObject ({width, height}, DrawPosition::BottomRight, block3);


    auto menu = new Menu (height * 0.13f, std::make_unique <ScreenCloseCommand> (this));
    menu->SetColumnWidth (width * 0.4);

    auto startGameButton = std::make_unique <Button> ("Start game", width * 0.3, std::make_unique <ScreenChangeCommand> (Screens::TETRIS_GAME, this));
    auto exitGameButton = std::make_unique <Button> ("Exit", width * 0.3, std::make_unique <ScreenCloseCommand> (this));

    menu->AddRow (std::move (startGameButton));
    menu->AddRow (std::move (exitGameButton));
    menu->SetInputLayer (Menu::GetStandardMenuInputLayer());

    m_inputHandler->PushInputLayer (menu->GetInputLayer());
    m_inputHandler->PushObject (menu);

    Vector2 menuPos {topCenter.x, topCenter.y + height * 0.45};
    m_screenGraphics.AddDrawableObject (menuPos, DrawPosition::Top, menu);
}

MainMenuScreen::~MainMenuScreen()
{
    m_inputHandler->PopInputLayer();
    m_inputHandler->PopObject();
}

void MainMenuScreen::Tick()
{
    m_screenGraphics.Draw();
}

void GameScreen::Tick()
{}
