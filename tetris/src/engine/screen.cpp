#include <engine/screen.h>

#include <graphics/animation.h>
#include <graphics/colors.h>
#include <graphics/decorative_block.h>
#include <graphics/graphics_helper.h>
#include <graphics/sprites.h>

#include <ui/ui_menu.h>
#include <ui/ui_button.h>


MainMenuScreen::MainMenuScreen (const ScreenSize& screenSize)
{
    float height = screenSize.m_height * screenSize.m_scale;
    float width = screenSize.m_width * screenSize.m_scale;
    DrawableContainerTools::AddRectangle (m_screenGraphics, {0.f, 0.f}, DrawPosition::TopLeft, height, width, Colors::darkBlue);

    int cellSize =35 * screenSize.m_scale;
    auto logoContainer = std::make_shared <DrawableContainer>();

    auto AddLetter = [cellSize] (DrawableContainer* cont, DrawableObject* letter) {
        auto bbox = cont->GetBoundingBox();
        Vector2 prevPos = GraphicsHelper::ComputePosition (DrawPosition::TopRight, bbox);
        cont->AddDrawableObject ({prevPos.x + cellSize/2, prevPos.y}, DrawPosition::TopLeft, letter);
    };

    auto blueT = SpriteGraphicGenerator::GetBlockLetterT (cellSize, Colors::blue, Colors::blue_shade);
    AddLetter (logoContainer.get(), blueT);

    auto yellowE = SpriteGraphicGenerator::GetBlockLetterE (cellSize, Colors::yellow, Colors::yellow_shade);
    AddLetter (logoContainer.get(), yellowE);

    auto greenT = SpriteGraphicGenerator::GetBlockLetterT (cellSize, Colors::green, Colors::green_shade);
    AddLetter (logoContainer.get(), greenT);

    auto redR = SpriteGraphicGenerator::GetBlockLetterR (cellSize, Colors::red, Colors::red_shade);
    AddLetter (logoContainer.get(), redR);

    auto cyanI = SpriteGraphicGenerator::GetBlockLetterI (cellSize, Colors::cyan, Colors::cyan_shade);
    AddLetter (logoContainer.get(), cyanI);

    auto purpleS = SpriteGraphicGenerator::GetBlockLetterS (cellSize, Colors::purple, Colors::purple_shade);
    AddLetter (logoContainer.get(), purpleS);

    auto screenBBox = m_screenGraphics.GetBoundingBox();
    Vector2 topCenter = GraphicsHelper::ComputePosition (DrawPosition::Top, screenBBox);

    Vector2 logoPos {topCenter.x, topCenter.y + height * 0.15};

    m_animLogo = new Animation (logoContainer);
    m_animLogo->AddMoveAnimStep (160, {0.f, -10.f});
    m_animLogo->AddMoveAnimStep (160, {0.f, 10.f});
    m_animLogo->EnableLooping();
    m_animLogo->Play();
    m_screenGraphics.AddDrawableObject (logoPos, DrawPosition::Top, m_animLogo);

    auto block1 = SpriteGraphicGenerator::GetMenuDecorativeBlock (cellSize);
    float posX = block1->GetBoundingBox().Width() + 1;
    m_screenGraphics.AddDrawableObject ({0, height}, DrawPosition::BottomLeft, block1);
    auto block2 = SpriteGraphicGenerator::GetMenuDecorativeBlockInversed (cellSize);
    if (auto bl = dynamic_cast <DecorativeBlock*> (block2)) {
        bl->AddCell ({3,0}, Colors::purple, Colors::purple_shade);
    }
    m_screenGraphics.AddDrawableObject ({posX, height + (cellSize + 1) * 2}, DrawPosition::BottomLeft, block2);
    auto block3 = SpriteGraphicGenerator::GetMenuDecorativeBlockInversed (cellSize);
    auto bboxB3 = m_screenGraphics.AddDrawableObject ({width + 15, height}, DrawPosition::BottomRight, block3)->GetBoundingBox();

    auto block4 = SpriteGraphicGenerator::GetMenuDecorativeBlock (cellSize);
    posX = bboxB3.Min().x + cellSize * 2 + 1;
    m_screenGraphics.AddDrawableObject ({posX, height + (cellSize + 1) * 3}, DrawPosition::BottomRight, block4);

    auto menu = new Menu (height * 0.13f, std::make_unique <ScreenCloseCommand> (this));
    menu->SetColumnWidth (width * 0.4);

    auto startGameButton = std::make_unique <Button> ("Start game", width * 0.3, std::make_unique <ScreenChangeCommand> (Screens::TETRIS_GAME, this));
    auto exitGameButton = std::make_unique <Button> ("Exit", width * 0.3, std::make_unique <ScreenCloseCommand> (this));

    menu->AddRow (std::move (startGameButton));
    menu->AddRow (std::move (exitGameButton));
    menu->SetInputLayer (Menu::GetStandardMenuInputLayer());

    InputHandler::GlobalInstance().AddLayer (menu->GetInputLayer(), menu);

    Vector2 menuPos {topCenter.x, topCenter.y + height * 0.45};
    m_screenGraphics.AddDrawableObject (menuPos, DrawPosition::Top, menu);
}

MainMenuScreen::~MainMenuScreen ()
{
    InputHandler::GlobalInstance().ReleaseLayer();
}

void MainMenuScreen::Update()
{
    m_animLogo->Update();
    m_screenGraphics.Draw();
}

void GameScreen::Update()
{}
