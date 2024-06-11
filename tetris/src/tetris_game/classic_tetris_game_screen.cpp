#include <tetris_game/classic_tetris_game_screen.h>

#include <engine/settings.h>
#include <graphics/colors.h>
#include <graphics/graphics_helper.h>
#include <ui/ui_button.h>

ClassicTetrisGameScreen::ClassicTetrisGameScreen (const ScreenSize& screenSize):
    m_pauseScreen (nullptr),
    m_inputHandler (std::make_unique<InputHandler>()),
    m_classicTetrisGame (&m_screenGraphics, m_inputHandler.get(), Settings::GamepadMappings(), Settings::KeyboardMappings()),
    m_screenSize (screenSize)
{
    m_screenGraphics.AddRectangle ({0.0},
        DrawPosition::TopLeft,
        screenSize.m_height * screenSize.m_scale,
        screenSize.m_width * screenSize.m_scale,
        Colors::darkBlue);
}

void ClassicTetrisGameScreen::Init()
{
    m_classicTetrisGame.Init();
    m_classicTetrisGame.AddObserver (this);
    m_classicTetrisGame.Start();
}

void ClassicTetrisGameScreen::Tick()
{
    m_inputHandler->Tick();
    m_classicTetrisGame.Tick();
    m_screenGraphics.Draw();
    m_classicTetrisGame.Draw();
    if (m_pauseScreen) {
        if (m_pauseScreen->IsActive()) {
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
        //ScreenSize subScreenSize {m_screenSize.m_width * 0.4f, m_screenSize.m_height * 0.4f, m_screenSize.m_scale};
        m_pauseScreen = new PauseSubScreen (m_screenSize, posCenter, m_inputHandler.get());
    }

}

ClassicTetrisGameScreen::PauseSubScreen::PauseSubScreen (const ScreenSize& size, Vector2 posCenter, InputHandler* iHandler):
    m_pauseMenu (nullptr),
    m_inputHandler (iHandler)
{
    float height = size.m_height * 0.4f * size.m_scale;
    float width = size.m_width * 0.4f * size.m_scale;
    m_screenGraphics.AddRectangle ({0.f, 0.f}, DrawPosition::Center, size.m_height * size.m_scale, size.m_width * size.m_scale, {0, 0, 0, 170}); //shadow
    auto mainFrame = m_screenGraphics.AddRectangle ({0.f, 0.f}, DrawPosition::Center, height, height, Colors::ghost);
    m_screenGraphics.AddRectangle ({0.f, 0.f}, DrawPosition::Center, height * 0.97, height * 0.97, Colors::darkestBlue);
    auto bbox = mainFrame->GetBoundingBox();
    float posX = 0;
    float posY = GraphicsHelper::ComputePosition (DrawPosition::Top, bbox).y;
    m_screenGraphics.AddText ({posX, posY + height * 0.17f}, DrawPosition::Center, "Game paused", height * 0.1, RAYWHITE);

    auto menu = std::make_unique <Menu> (height * 0.5, std::make_unique <ScreenCloseCommand> (this));
    menu->SetColumnWidth (width);
    auto buttonContinue = std::make_unique <Button> ("Continue", width * 0.7, std::make_unique <ScreenCloseCommand> (this));
    menu->AddRow (std::move (buttonContinue));
    m_pauseMenu = menu.get();
    m_screenGraphics.AddDrawableObject ({posX, posY + height * 0.22f}, DrawPosition::Top, std::move (menu));

    m_inputLayer.AddAction (GAMEPAD_BUTTON_LEFT_FACE_DOWN, KEY_ENTER, ActionType::PRESS, std::make_unique <MenuSelectCommand>());
    m_inputLayer.AddAction (GAMEPAD_BUTTON_RIGHT_FACE_DOWN, KEY_DOWN, ActionType::PRESS, std::make_unique <MenuMoveDownCommand>());
    m_inputLayer.AddAction (GAMEPAD_BUTTON_RIGHT_FACE_UP, KEY_UP, ActionType::PRESS, std::make_unique <MenuMoveUpCommand>());
    m_inputLayer.AddAction (GAMEPAD_BUTTON_RIGHT_FACE_LEFT, KEY_LEFT, ActionType::PRESS, std::make_unique <MenuMoveLeftCommand>());
    m_inputLayer.AddAction (GAMEPAD_BUTTON_RIGHT_FACE_RIGHT, KEY_RIGHT, ActionType::PRESS, std::make_unique <MenuMoveRightCommand>());
    m_inputLayer.AddAction (GAMEPAD_BUTTON_LEFT_FACE_RIGHT, KEY_ESCAPE, ActionType::PRESS, std::make_unique <MenuExitCommand>());

    m_inputHandler->PushInputLayer (&m_inputLayer);
    m_inputHandler->PushObject (m_pauseMenu);

    m_screenGraphics.Translate (posCenter);
}

ClassicTetrisGameScreen::PauseSubScreen::~PauseSubScreen()
{
    m_inputHandler->PopInputLayer();
    m_inputHandler->PopObject();
}
