#include <tetris_game/title_screen.h>

#include <engine/audio_manager.h>

#include <graphics/animation.h>
#include <graphics/colors.h>
#include <graphics/decorative_block.h>
#include <graphics/graphics_helper.h>
#include <graphics/sprites.h>

#include <ui/ui_menu.h>
#include <ui/ui_button.h>

TitleScreen::TitleScreen (const ScreenSize& screenSize):
    m_animIdx (0),
    m_bIsreadyForGame (false)
{
    float height = screenSize.m_height * screenSize.m_scale;
    float width = screenSize.m_width * screenSize.m_scale;
    DrawableContainerTools::AddRectangle (m_screenGraphics, {0.f, 0.f}, DrawPosition::TopLeft, height, width, Colors::darkBlue);

    int cellSize = 35 * screenSize.m_scale;
    auto logoContainer = std::make_shared <DrawableContainer>();

    auto AddLetter = [cellSize] (DrawableContainer* cont, DrawableObject* letter) {
        auto bbox = cont->GetBoundingBox();
        Vector2 prevPos = GraphicsHelper::ComputePosition (DrawPosition::TopRight, bbox);
        cont->AddDrawableObject ({prevPos.x + cellSize/2, prevPos.y}, DrawPosition::TopLeft, letter);
    };

    std::shared_ptr <DrawableObject> blueT (SpriteGraphicGenerator::GetBlockLetterT (cellSize, Colors::blue, Colors::blue_shade));
    auto animBlueT = new Animation (blueT);
    AddLetter (logoContainer.get(), animBlueT);

    std::shared_ptr <DrawableObject>  yellowE (SpriteGraphicGenerator::GetBlockLetterE (cellSize, Colors::yellow, Colors::yellow_shade));
    auto animYellowE = new Animation (yellowE);
    AddLetter (logoContainer.get(), animYellowE);

    std::shared_ptr <DrawableObject>  greenT (SpriteGraphicGenerator::GetBlockLetterT (cellSize, Colors::green, Colors::green_shade));
    auto animGreenT = new Animation (greenT);
    AddLetter (logoContainer.get(), animGreenT);

    std::shared_ptr <DrawableObject>  redR (SpriteGraphicGenerator::GetBlockLetterR (cellSize, Colors::red, Colors::red_shade));
    auto animRedR = new Animation (redR);
    AddLetter (logoContainer.get(), animRedR);

    std::shared_ptr <DrawableObject>  cyanI (SpriteGraphicGenerator::GetBlockLetterI (cellSize, Colors::cyan, Colors::cyan_shade));
    auto animCyanI = new Animation (cyanI);
    AddLetter (logoContainer.get(), animCyanI);

    std::shared_ptr <DrawableObject>  purpleS (SpriteGraphicGenerator::GetBlockLetterS (cellSize, Colors::purple, Colors::purple_shade));
    auto animPurpleS = new Animation (purpleS);
    AddLetter (logoContainer.get(), animPurpleS);

    auto screenBBox = m_screenGraphics.GetBoundingBox();
    Vector2 topCenter = GraphicsHelper::ComputePosition (DrawPosition::Top, screenBBox);

    Vector2 logoPos {topCenter.x, topCenter.y + height * 0.3f};
    auto animLogo = new Animation (logoContainer);
    m_screenGraphics.AddDrawableObject (logoPos, DrawPosition::Top, animLogo);
    auto logoBBox = logoContainer->GetBoundingBox();

    auto FillMoveAnim = [] (Animation* anim, std::vector <Animation*>& anims)
    {
        auto pos = anim->GetPosition();
        auto bbox = anim->GetBoundingBox();

        Vector2 initPos {-(bbox.Width() + 10), pos.y};
        anim->Translate (GraphicsHelper::ComputeTranslation (pos, initPos));
        anim->AddMoveAnimStep (25, GraphicsHelper::ComputeTranslation (initPos, pos));
        anim->Play();
        anims.push_back (anim);

        return anim;
    };

    animRedR->AddWaitAnimStep (40);
    FillMoveAnim (animRedR, m_animsLogo);
    FillMoveAnim (animGreenT, m_animsLogo);
    FillMoveAnim (animYellowE, m_animsLogo);
    FillMoveAnim (animBlueT, m_animsLogo);

    auto posS = animPurpleS->GetPosition();
    auto bboxS = animPurpleS->GetBoundingBox();

    Vector2 initPosS {width + bboxS.Width(), posS.y};
    animPurpleS->Translate (GraphicsHelper::ComputeTranslation (posS, initPosS));
    animPurpleS->AddMoveAnimStep (34, GraphicsHelper::ComputeTranslation (initPosS, posS));
    animPurpleS->Play();
    m_animsLogo.push_back (animPurpleS);

    auto posI = animCyanI->GetPosition();
    auto bboxI = animCyanI->GetBoundingBox();

    Vector2 initPosI {posI.x, -(bboxI.Height() + 10)};
    animCyanI->Translate (GraphicsHelper::ComputeTranslation (posI, initPosI));
    animCyanI->AddWaitAnimStep (27);
    animCyanI->AddMoveAnimStep (25, GraphicsHelper::ComputeTranslation (initPosI, posI));
    animCyanI->Play();
    m_animsLogo.push_back (animCyanI);

    int dBlockCellSize = 35 * screenSize.m_scale;
    std::shared_ptr <DrawableObject> block1 (SpriteGraphicGenerator::GetMenuDecorativeBlock (dBlockCellSize));
    auto animBlock1 = new Animation (block1);
    float posX = block1->GetBoundingBox().Width() + 1;
    m_screenGraphics.AddDrawableObject ({0, height}, DrawPosition::BottomLeft, animBlock1);
    std::shared_ptr <DrawableObject> block2 (SpriteGraphicGenerator::GetMenuDecorativeBlockInversed (dBlockCellSize));
    auto animBlock2 = new Animation (block2);
    if (auto bl = dynamic_cast <DecorativeBlock*> (block2.get())) {
        bl->AddCell ({3,0}, Colors::purple, Colors::purple_shade);
    }
    m_screenGraphics.AddDrawableObject ({posX, height + (dBlockCellSize + 1) * 2}, DrawPosition::BottomLeft, animBlock2);
    std::shared_ptr <DrawableObject> block3 (SpriteGraphicGenerator::GetMenuDecorativeBlockInversed (dBlockCellSize));
    auto animBlock3 = new Animation (block3);
    auto bboxB3 = m_screenGraphics.AddDrawableObject ({width + 15, height}, DrawPosition::BottomRight, animBlock3)->GetBoundingBox();

    std::shared_ptr <DrawableObject> block4 (SpriteGraphicGenerator::GetMenuDecorativeBlock (dBlockCellSize));
    auto animBlock4 = new Animation (block4);
    posX = bboxB3.Min().x + dBlockCellSize * 2 + 1;
    m_screenGraphics.AddDrawableObject ({posX, height + (dBlockCellSize + 1) * 3}, DrawPosition::BottomRight, animBlock4);

    auto FillBlockAnim = [&screenSize](Animation* anim, std::vector <Animation*>& anims)
    {
        auto pos = anim->GetPosition();
        auto bbox = anim->GetBoundingBox();

        Vector2 initPos {pos.x, screenSize.m_height * screenSize.m_scale};
        anim->Translate (GraphicsHelper::ComputeTranslation (pos, initPos));
        anim->AddMoveAnimStep (52, GraphicsHelper::ComputeTranslation (initPos, pos));
        anims.push_back (anim);

        return anim;
    };

    FillBlockAnim (animBlock1, m_animsBlocks);
    FillBlockAnim (animBlock2, m_animsBlocks);
    FillBlockAnim (animBlock3, m_animsBlocks);
    FillBlockAnim (animBlock4, m_animsBlocks);

    Vector2 pressPlayPos {topCenter.x, topCenter.y + height * 0.6f};
    auto pressPlay = std::make_shared <DrawableContainer>();
    DrawableContainerTools::AddText (*pressPlay, {0.f, 0.f}, DrawPosition::Left, "Press  ", height * 0.04f, RAYWHITE);
    pressPlay->AddDrawableObject (GraphicsHelper::ComputePosition (DrawPosition::Right, pressPlay->GetBoundingBox()), DrawPosition::Left, SpriteGraphicGenerator::GetKeybordKey (KEY_ENTER, 39 * screenSize.m_scale));
    DrawableContainerTools::AddText (*pressPlay, GraphicsHelper::ComputePosition (DrawPosition::Right, pressPlay->GetBoundingBox()), DrawPosition::Left, " / ", height * 0.04f, RAYWHITE);
    pressPlay->AddDrawableObject (GraphicsHelper::ComputePosition (DrawPosition::Right, pressPlay->GetBoundingBox()), DrawPosition::Left, SpriteGraphicGenerator::GetXBoxButtonA (29 * screenSize.m_scale));
    DrawableContainerTools::AddText (*pressPlay, GraphicsHelper::ComputePosition (DrawPosition::Right, pressPlay->GetBoundingBox()), DrawPosition::Left, "  to start", height * 0.04f, RAYWHITE);
    pressPlay->SetAlpha (0);
    auto animPress = new Animation (pressPlay);
    animPress->AddSetOpacityAnimStep (20, 0);
    animPress->AddChangeOpacityAnimStep (100, 255);
    animPress->AddSetOpacityAnimStep (40, 255);
    animPress->AddChangeOpacityAnimStep (100, 0);
    animPress->EnableLooping();
    m_animPress = animPress;
    m_screenGraphics.AddDrawableObject (pressPlayPos, DrawPosition::Top, animPress);

    Vector2 flashMin {logoBBox.Min().x-logoBBox.Width() * 0.5f, logoBBox.Min().y - logoBBox.Height() * 0.6f};
    Vector2 flashMax {logoBBox.Max().x + logoBBox.Width() * 0.5f, logoBBox.Max().y + logoBBox.Height() * 0.6f};
    BoundingBox2d flashBBox (flashMin, flashMax);
    auto flash = std::make_shared <shapes::Rectangle> (flashBBox);
    flash->SetAlign (DrawPosition::Center);
    flash->SetColor (RAYWHITE);
    flash->SetAlpha (0);
    auto animFlash = new Animation (flash);
    m_screenGraphics.AddDrawableObject (GraphicsHelper::ComputePosition (DrawPosition::Center, logoBBox), DrawPosition::Center, animFlash);

    auto AddFlashSequence = [animFlash] (unsigned char opacity) {
        int length = 6;
        animFlash->AddChangeOpacityAnimStep (length, opacity);
        animFlash->AddScaleAnimStep (length, 1.3f, true);
        animFlash->AddChangeOpacityAnimStep (length, 0);
        animFlash->AddScaleAnimStep (length, 1.3f, true);
    };

    AddFlashSequence (250);
    AddFlashSequence (220);
    AddFlashSequence (190);
    AddFlashSequence (255);

    animFlash->Play();
    m_animsLogo.push_back (animFlash);

    animLogo->AddMoveAnimStep (160, {0.f, -10.f});
    animLogo->AddMoveAnimStep (160, {0.f, 10.f});
    animLogo->EnableLooping();
    animLogo->Play();
    m_animsLogo.push_back (animLogo);

    auto hiddenMenu = new Menu (10.f, std::make_unique <ScreenCloseCommand> (this));
    auto startButton = std::make_unique <Button> ("Start", 20.f, std::make_unique <SetReadyCommand> (this));
    hiddenMenu->AddRow (std::move (startButton));

    InputLayer layer;
    layer.AddAction (GAMEPAD_BUTTON_RIGHT_FACE_DOWN, KEY_ENTER, ActionType::PRESS, std::make_unique <MenuSelectCommand>());
    hiddenMenu->SetInputLayer (std::move (layer));
    hiddenMenu->SetInvisible();
    m_screenGraphics.AddDrawableObject ({-20.f, -20.f}, DrawPosition::BottomRight, hiddenMenu);

    InputHandler::GlobalInstance().AddLayer (hiddenMenu->GetInputLayer(), hiddenMenu);

    m_screenExitAnimation = new Animation (logoContainer);
    Vector2 menuLogoPos {logoContainer->GetPosition().x, topCenter.y + height * 0.15};
    m_screenExitAnimation->AddWaitAnimStep (27);
    m_screenExitAnimation->AddMoveToAnimStep (60, menuLogoPos);
}

TitleScreen::~TitleScreen()
{
    InputHandler::GlobalInstance().ReleaseLayer();
}

void TitleScreen::Update()
{
    if (m_animIdx < m_animsLogo.size()) {
        m_animsLogo[m_animIdx]->Update();
        if (!m_animsLogo[m_animIdx]->IsPlaying()) {
            if (m_animIdx < m_animsLogo.size() - 3) {
                AudioManager::GetInstance().Play ("block_drop");
            } else if (m_animIdx == m_animsLogo.size() - 3) {
                for (auto& anim: m_animsBlocks) {
                    anim->Play();
                }
                AudioManager::GetInstance().Play ("flash");
            }
            m_animIdx++;
        }
        if (m_animIdx == m_animsLogo.size() - 1) {
            m_animPress->Play();
            m_animIdx++;
        }
    }

    m_animPress->Update();
    if (m_animIdx == m_animsLogo.size()) {
        m_animsLogo.back()->Update();
    }
    for (auto& anim: m_animsBlocks) {
        if (anim->IsPlaying()) {
            anim->Update();
        }
    }
    if (m_bIsreadyForGame && m_animIdx == m_animsLogo.size()) {
        m_animsLogo.back()->Pause();
        m_animPress->Pause();
        m_animPress->SetInvisible();
        m_screenExitAnimation->Play();
    } else if (m_bIsreadyForGame) {
        SetNextScreen (Screens::MAIN_MENU);
    }
    m_screenExitAnimation->Update();
    m_screenGraphics.Draw();
    if (m_screenExitAnimation->IsCompleted()) {
        SetNextScreen (Screens::MAIN_MENU);
    }
}
