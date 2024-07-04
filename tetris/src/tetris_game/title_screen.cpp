#include <tetris_game/title_screen.h>

#include <engine/audio_manager.h>

#include <graphics/animation.h>
#include <graphics/colors.h>
#include <graphics/decorative_block.h>
#include <graphics/graphics_helper.h>
#include <graphics/sprites.h>

TitleScreen::TitleScreen (InputHandler* iHandler, const ScreenSize& screenSize):
    Screen (iHandler),
    m_animIdx (0)
{
    float height = screenSize.m_height * screenSize.m_scale;
    float width = screenSize.m_width * screenSize.m_scale;
    m_screenGraphics.AddRectangle ({0.f, 0.f}, DrawPosition::TopLeft, height, width, Colors::darkBlue);

    int cellSize = 35 * screenSize.m_scale;
    auto logoContainer = new DrawableContainer();

    auto AddLetter = [cellSize] (DrawableContainer* cont, DrawableObject* letter) {
        auto bbox = cont->GetBoundingBox();
        Vector2 prevPos = GraphicsHelper::ComputePosition (DrawPosition::TopRight, bbox);
        cont->AddDrawableObject ({prevPos.x + cellSize/2, prevPos.y}, DrawPosition::TopLeft, letter);
    };

    auto blueT = SpriteGraphicGenerator::GetBlockLetterT (cellSize, Colors::blue, Colors::blue_shade);
    auto animBlueT = new Animation (blueT);
    AddLetter (logoContainer, animBlueT);

    auto yellowE = SpriteGraphicGenerator::GetBlockLetterE (cellSize, Colors::yellow, Colors::yellow_shade);
    auto animYellowE = new Animation (yellowE);
    AddLetter (logoContainer, animYellowE);

    auto greenT = SpriteGraphicGenerator::GetBlockLetterT (cellSize, Colors::green, Colors::green_shade);
    auto animGreenT = new Animation (greenT);
    AddLetter (logoContainer, animGreenT);

    auto redR = SpriteGraphicGenerator::GetBlockLetterR (cellSize, Colors::red, Colors::red_shade);
    auto animRedR = new Animation (redR);
    AddLetter (logoContainer, animRedR);

    auto cyanI = SpriteGraphicGenerator::GetBlockLetterI (cellSize, Colors::cyan, Colors::cyan_shade);
    auto animCyanI = new Animation (cyanI);
    AddLetter (logoContainer, animCyanI);

    auto purpleS = SpriteGraphicGenerator::GetBlockLetterS (cellSize, Colors::purple, Colors::purple_shade);
    auto animPurpleS = new Animation (purpleS);
    AddLetter (logoContainer, animPurpleS);

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

    Vector2 initPosS {screenSize.m_width + 2.f, posS.y};
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
    auto block1 = SpriteGraphicGenerator::GetMenuDecorativeBlock (dBlockCellSize);
    auto animBlock1 = new Animation (block1);
    float posX = block1->GetBoundingBox().Width() + 1;
    m_screenGraphics.AddDrawableObject ({0, height}, DrawPosition::BottomLeft, animBlock1);
    auto block2 = SpriteGraphicGenerator::GetMenuDecorativeBlockInversed (dBlockCellSize);
    auto animBlock2 = new Animation (block2);
    if (auto bl = dynamic_cast <DecorativeBlock*> (block2)) {
        bl->AddCell ({3,0}, Colors::purple, Colors::purple_shade);
    }
    m_screenGraphics.AddDrawableObject ({posX, height + (dBlockCellSize + 1) * 2}, DrawPosition::BottomLeft, animBlock2);
    auto block3 = SpriteGraphicGenerator::GetMenuDecorativeBlockInversed (dBlockCellSize);
    auto animBlock3 = new Animation (block3);
    m_screenGraphics.AddDrawableObject ({width, height}, DrawPosition::BottomRight, animBlock3);

    auto FillBlockAnim = [&screenSize](Animation* anim, std::vector <Animation*>& anims)
    {
        auto pos = anim->GetPosition();
        auto bbox = anim->GetBoundingBox();

        Vector2 initPos {pos.x, (float)screenSize.m_height};
        anim->Translate (GraphicsHelper::ComputeTranslation (pos, initPos));
        anim->AddMoveAnimStep (52, GraphicsHelper::ComputeTranslation (initPos, pos));
        anims.push_back (anim);

        return anim;
    };

    FillBlockAnim (animBlock1, m_animsBlocks);
    FillBlockAnim (animBlock2, m_animsBlocks);
    FillBlockAnim (animBlock3, m_animsBlocks);

    Vector2 pressPlayPos {topCenter.x, topCenter.y + height * 0.6f};
    auto pressText = m_screenGraphics.AddText (pressPlayPos, DrawPosition::Top, "Press ENTER to play", screenSize.m_height * 0.05f, RAYWHITE);
    pressText->SetAlpha (0);
    auto animPress = new Animation (pressText);
    animPress->AddSetOpacityAnimStep (20, 0);
    animPress->AddChangeOpacityAnimStep (100, 255);
    animPress->AddSetOpacityAnimStep (20, 255);
    animPress->AddChangeOpacityAnimStep (100, 0);
    m_animPress = animPress;

    Vector2 flashMin {logoBBox.Min().x-logoBBox.Width() * 0.5f, logoBBox.Min().y - logoBBox.Height() * 0.6f};
    Vector2 flashMax {logoBBox.Max().x + logoBBox.Width() * 0.5f, logoBBox.Max().y + logoBBox.Height() * 0.6f};
    BoundingBox2d flashBBox (flashMin, flashMax);
    auto flash = m_screenGraphics.AddRectangle (GraphicsHelper::ComputePosition (DrawPosition::Center, logoBBox), DrawPosition::Center, flashBBox.Height(), flashBBox.Width(), RAYWHITE);
    flash->SetAlpha (0);

    auto animFlash = new Animation (flash);
    auto AddFlashSequence = [animFlash] (unsigned char opacity) {
        int length = 6;
        animFlash->AddChangeOpacityAnimStep (length, opacity);
        animFlash->AddScaleAnimStep (length, 1.3f, true);
        animFlash->AddChangeOpacityAnimStep (length, 0);
        animFlash->AddScaleAnimStep (length, 1.3f, true);
    };

    //animFlash->SetAlpha (160);

    AddFlashSequence (250);
    AddFlashSequence (220);
    AddFlashSequence (190);
    AddFlashSequence (255);

    animFlash->Play();
    m_animsLogo.push_back (animFlash);

    Sequence idleMoveUp;
    animLogo->AddMoveAnimStep (160, {0.f, -10.f});
    animLogo->AddMoveAnimStep (160, {0.f, 10.f});
    animLogo->EnableLooping();
    animLogo->Play();
    m_animsLogo.push_back (animLogo);
}

void TitleScreen::Tick()
{
    if (m_animIdx < m_animsLogo.size()) {
        m_animsLogo[m_animIdx]->Tick();
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
        }
    }

    m_animPress->Tick();
    for (auto& anim: m_animsBlocks) {
        if (anim->IsPlaying()) {
            anim->Tick();
        }
    }
    m_screenGraphics.Draw();
}
