#include <tetris_game/classic_tetris_game_screen.h>

#include <engine/settings.h>
#include <graphics/colors.h>
#include <graphics/graphics_helper.h>

#include <ui/ui_button.h>
#include <ui/ui_mapped_key.h>

ClassicTetrisGameScreen::ClassicTetrisGameScreen (const ScreenSize& screenSize, InputHandler* iHandler):
    Screen (iHandler),
    m_pauseScreen (nullptr),
    m_classicTetrisGame (&m_screenGraphics, m_inputHandler, screenSize.m_scale, Settings::GamepadMappings(), Settings::KeyboardMappings()),
    m_screenSize (screenSize)
{
    m_screenGraphics.AddRectangle ({0.0},
        DrawPosition::TopLeft,
        screenSize.m_height * screenSize.m_scale,
        screenSize.m_width * screenSize.m_scale,
        Colors::darkBlue);

    m_classicTetrisGame.Init();
    m_classicTetrisGame.AddObserver (this);
    m_classicTetrisGame.Start();
}


void ClassicTetrisGameScreen::Tick()
{
    m_classicTetrisGame.Tick();
    m_screenGraphics.Draw();
    m_classicTetrisGame.Draw();
    if (m_pauseScreen) {
        if (m_pauseScreen->IsActive()) {
            if (m_pauseScreen->DoesWantToChangeScreen()) {
                SetNextScreen (m_pauseScreen->GetNextScreen());
            }
            m_pauseScreen->Draw();
        } else {
            delete m_pauseScreen;
            m_pauseScreen = nullptr;
            m_classicTetrisGame.Unpause();
        }
    }
}

void ClassicTetrisGameScreen::onNotify (const Object& obj, Event e)
{
    if (e == Event::PAUSE) {
        Vector2 posCenter = GraphicsHelper::ComputePosition (DrawPosition::Center, m_screenGraphics.GetBoundingBox());
        m_pauseScreen = new PauseSubScreen (m_screenSize, posCenter, m_inputHandler, Settings::KeyboardMappings(), Settings::GamepadMappings());
    }

}

ClassicTetrisGameScreen::PauseSubScreen::PauseSubScreen (
    const ScreenSize& size,
    Vector2 posCenter,
    InputHandler* iHandler,
    const Settings::KeyboardMappings& kMap,
    const Settings::GamepadMappings& gMap):
    Screen (iHandler),
    m_pauseMenu (nullptr)
{
    float height = size.m_height * 0.4f * size.m_scale;
    float width = size.m_width * 0.4f * size.m_scale;
    auto mainShadowing = m_screenGraphics.AddRectangle ({0.f, 0.f}, DrawPosition::Center, size.m_height * size.m_scale, size.m_width * size.m_scale, {0, 0, 0, 170}); //shadow
    auto contentFrame = m_screenGraphics.AddRectangle ({0.f, 0.f}, DrawPosition::Center, height, height, Colors::ghost);
    m_screenGraphics.AddRectangle ({0.f, 0.f}, DrawPosition::Center, height * 0.97, height * 0.97, Colors::darkestBlue);
    auto bbox = contentFrame->GetBoundingBox();
    float posX = 0;
    float posY = GraphicsHelper::ComputePosition (DrawPosition::Top, bbox).y;
    m_screenGraphics.AddText ({posX, posY + height * 0.17f}, DrawPosition::Center, "Game paused", height * 0.1, RAYWHITE);

    m_pauseMenu = new Menu (height * 0.31, std::make_unique <ScreenCloseCommand> (this));
    m_pauseMenu->SetColumnWidth (width);
    auto buttonContinue = std::make_unique <Button> ("Continue", width * 0.7, std::make_unique <ScreenCloseCommand> (this));
    auto buttonExit = std::make_unique <Button> ("Main menu", width * 0.7, std::make_unique <ScreenChangeCommand> (Screens::MAIN_MENU, this));
    m_pauseMenu->AddRow (std::move (buttonContinue));
    m_pauseMenu->AddRow (std::move (buttonExit));
    m_screenGraphics.AddDrawableObject ({posX, posY + height * 0.31f}, DrawPosition::Top, m_pauseMenu);

    m_inputLayer = Menu::GetStandardMenuInputLayer();

    m_inputHandler->PushInputLayer (&m_inputLayer);
    m_inputHandler->PushObject (m_pauseMenu);


    auto AddMapping = [height, width, &posY] (KeyboardKey key, GamepadButton button, const InputHandler* iHandler, std::string text, DrawableContainer* cont) {
        auto mappedKey = new MappedKey (key, button, iHandler, height * 0.15f);
        cont->AddDrawableObject ({0., posY}, DrawPosition::TopLeft, mappedKey);

        Vector2 textPos = GraphicsHelper::ComputePosition (DrawPosition::Right, mappedKey->GetBoundingBox());
        cont->AddText ({textPos.x + width * 0.04f, textPos.y}, DrawPosition::Left, text, height * 0.08f, RAYWHITE);
        posY = mappedKey->GetBoundingBox().Max().y + height * 0.05f;
    };

    auto controlsContainer = new DrawableContainer();
    posY = controlsContainer->AddText ({0., 0.}, DrawPosition::TopLeft, "Controls", height * 0.12f, RAYWHITE)->GetBoundingBox().Max().y + height * 0.07f;

    AddMapping (kMap.m_HoldKey, gMap.m_HoldButton, m_inputHandler, " - Hold", controlsContainer);
    AddMapping (kMap.m_HardDropKey, gMap.m_HardDropButton, m_inputHandler, " - Hard drop", controlsContainer);
    AddMapping (kMap.m_RotateKey, gMap.m_RotateButton, m_inputHandler, " - Rotate", controlsContainer);
    AddMapping (kMap.m_MoveLeftKey, GAMEPAD_BUTTON_LEFT_FACE_LEFT, m_inputHandler, " - Move left", controlsContainer);
    AddMapping (kMap.m_MoveRightKey, GAMEPAD_BUTTON_LEFT_FACE_RIGHT, m_inputHandler, " - Move right", controlsContainer);
    AddMapping (kMap.m_MoveDown, GAMEPAD_BUTTON_LEFT_FACE_DOWN, m_inputHandler, " - Move down", controlsContainer);

    Vector2 controlsPos = GraphicsHelper::ComputePosition (DrawPosition::Left, mainShadowing->GetBoundingBox());
    m_screenGraphics.AddDrawableObject ({controlsPos.x + width * 0.1f, controlsPos.y}, DrawPosition::Left, controlsContainer);

    m_screenGraphics.Translate (posCenter);
}

ClassicTetrisGameScreen::PauseSubScreen::~PauseSubScreen()
{
    m_inputHandler->PopInputLayer();
    m_inputHandler->PopObject();
}
