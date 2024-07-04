#include <tetris_game/classic_tetris_game_screen.h>

#include <engine/settings.h>

#include <graphics/animation.h>
#include <graphics/colors.h>
#include <graphics/graphics_helper.h>
#include <graphics/shapes.h>

#include <ui/ui_button.h>
#include <ui/ui_mapped_key.h>
#include <ui/ui_table.h>

ClassicTetrisGameScreen::ClassicTetrisGameScreen (const ScreenSize& screenSize, InputHandler* iHandler):
    Screen (iHandler),
    m_pauseScreen (nullptr),
    m_gameOverScreen (nullptr),
    m_classicTetrisGame (&m_screenGraphics, m_inputHandler, screenSize.m_scale, Settings::GetInstance().GetGamepadMappings(), Settings::GetInstance().GetKeyboardMappings()),
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
    auto path = std::filesystem::current_path();
    path /= "data/scores.sav";
    if (!HighScoresSavReader().Read (path, m_gameScores))
    {
        std::cout << "Failed to load save file";
    }
}

ClassicTetrisGameScreen::~ClassicTetrisGameScreen()
{
    if (m_pauseScreen) {
        delete m_pauseScreen;
    }
    if (m_gameOverScreen) {
        delete m_gameOverScreen;
    }
    auto path = std::filesystem::current_path();
    path /= "data";
    if (!HighScoresSavWriter().Write (m_gameScores, path, L"scores.sav"))
    {
        std::cout << "Failed to write save file";
    }
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
    if (m_gameOverScreen) {
        if (m_gameOverScreen->IsActive()) {
            if (m_gameOverScreen->DoesWantToChangeScreen()) {
                SetNextScreen (m_gameOverScreen->GetNextScreen());
                m_gameOverScreen->SetToClose();
            }
            m_gameOverScreen->Draw();
        } else {
            delete m_gameOverScreen;
            m_gameOverScreen = nullptr;
        }
    }
}

void ClassicTetrisGameScreen::onNotify (const Object& obj, Event e)
{
    switch (e)
    {
    case Event::PAUSE:
    {
        Vector2 posCenter = GraphicsHelper::ComputePosition (DrawPosition::Center, m_screenGraphics.GetBoundingBox());
        m_pauseScreen = new PauseSubScreen (m_screenSize, posCenter, m_inputHandler, settings::KeyboardMappings(), settings::GamepadMappings());
        m_pauseScreen->AddObserver (this);
        break;
    }
    case Event::GAME_OVER:
    {
        Vector2 posCenter = GraphicsHelper::ComputePosition (DrawPosition::Center, m_screenGraphics.GetBoundingBox());
        if (auto game = dynamic_cast <const ClassicTetrisGame*> (&obj)) {
            m_gameOverScreen = new GameOverSubScreen (m_screenSize, posCenter, game->GetScore(), m_inputHandler);
            m_gameScores.AddNewScore (game->GetScore(), game->GetNumLinesRemoved());
            m_gameOverScreen->AddObserver (this);
        }
        break;
    }
    case Event::GAME_RESET:
        m_classicTetrisGame.Reset();
        m_classicTetrisGame.Start();
        break;
    default:
        break;
    }

}

class PauseSubScreenRestartCommand: public CommandWithContext
{
public:
    PauseSubScreenRestartCommand (Screen* screen):
        CommandWithContext (screen)
    {}

    virtual bool Execute (Object* obj) override
    {
        if (auto screen = dynamic_cast <ClassicTetrisGameScreen::PauseSubScreen*> (obj)) {
            screen->NotifyGameReset();
            screen->SetToClose();
            return true;
        }
        return false;
    }
};


ClassicTetrisGameScreen::PauseSubScreen::PauseSubScreen (
    const ScreenSize& size,
    Vector2 posCenter,
    InputHandler* iHandler,
    const settings::KeyboardMappings& kMap,
    const settings::GamepadMappings& gMap):
    Screen (iHandler),
    m_pauseMenu (nullptr)
{
    float height = size.m_height * 0.6f * size.m_scale;
    float width = size.m_width * 0.4f * size.m_scale;
    auto mainShadowing = m_screenGraphics.AddRectangle ({0.f, 0.f}, DrawPosition::Center, size.m_height * size.m_scale, size.m_width * size.m_scale, {0, 0, 0, 170}); //shadow
    auto contentFrame = m_screenGraphics.AddRectangle ({0.f, 0.f}, DrawPosition::Center, height, width, Colors::ghost);
    m_screenGraphics.AddRectangle ({0.f, 0.f}, DrawPosition::Center, height * 0.97, width * 0.97, Colors::darkestBlue);
    auto bbox = contentFrame->GetBoundingBox();
    float posX = 0;
    float posY = GraphicsHelper::ComputePosition (DrawPosition::Top, bbox).y;
    m_screenGraphics.AddText ({posX, posY + height * 0.15f}, DrawPosition::Center, "Game paused", height * 0.1, RAYWHITE);

    m_pauseMenu = new Menu (height * 0.21, std::make_unique <ScreenCloseCommand> (this));
    m_pauseMenu->SetColumnWidth (width);
    auto buttonContinue = std::make_unique <Button> ("Continue", width * 0.7, std::make_unique <ScreenCloseCommand> (this));
    auto buttonReset = std::make_unique <Button> ("Restart", width * 0.7, std::make_unique <PauseSubScreenRestartCommand> (this));
    auto buttonExit = std::make_unique <Button> ("Main menu", width * 0.7, std::make_unique <ScreenChangeCommand> (Screens::MAIN_MENU, this));
    m_pauseMenu->AddRow (std::move (buttonContinue));
    m_pauseMenu->AddRow (std::move (buttonReset));
    m_pauseMenu->AddRow (std::move (buttonExit));
    m_screenGraphics.AddDrawableObject ({posX, posY + height * 0.31f}, DrawPosition::Top, m_pauseMenu);

    m_inputLayer = Menu::GetStandardMenuInputLayer();

    m_inputHandler->PushInputLayer (&m_inputLayer);
    m_inputHandler->PushObject (m_pauseMenu);


    auto AddMapping = [height, width, &posY] (KeyboardKey key, GamepadButton button, const InputHandler* iHandler, std::string text, DrawableContainer* cont) {
        auto mappedKey = new MappedKey (key, button, iHandler, height * 0.09f);
        cont->AddDrawableObject ({0., posY}, DrawPosition::TopLeft, mappedKey);

        Vector2 textPos = GraphicsHelper::ComputePosition (DrawPosition::Right, mappedKey->GetBoundingBox());
        cont->AddText ({textPos.x + width * 0.04f, textPos.y}, DrawPosition::Left, text, height * 0.05f, RAYWHITE);
        posY = mappedKey->GetBoundingBox().Max().y + height * 0.05f;
    };

    auto controlsContainer = new DrawableContainer();
    posY = controlsContainer->AddText ({0., 0.}, DrawPosition::TopLeft, "Controls", height * 0.08f, RAYWHITE)->GetBoundingBox().Max().y + height * 0.04f;

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

void ClassicTetrisGameScreen::PauseSubScreen::NotifyGameReset()
{
    Notify (*this, Event::GAME_RESET);
}

ClassicTetrisGameScreen::PauseSubScreen::~PauseSubScreen()
{
    m_inputHandler->PopInputLayer();
    m_inputHandler->PopObject();
}

class GOSubScreenRestartCommand: public CommandWithContext
{
public:
    GOSubScreenRestartCommand (Screen* screen):
        CommandWithContext (screen)
    {}

    virtual bool Execute (Object* obj) override
    {
        if (auto screen = dynamic_cast <ClassicTetrisGameScreen::GameOverSubScreen*> (obj)) {
            screen->NotifyGameReset();
            screen->SetToClose();
            return true;
        }
        return false;
    }
};


ClassicTetrisGameScreen::GameOverSubScreen::GameOverSubScreen (const ScreenSize& size, Vector2 posCenter, size_t score, InputHandler* iHandler):
    Screen (iHandler),
    m_gameOverMenu (nullptr)
{
    float height = size.m_height * 0.5f * size.m_scale;
    float width = size.m_width * 0.7f * size.m_scale;

    auto mainShadowing = m_screenGraphics.AddRectangle ({0.f, 0.f}, DrawPosition::Center, size.m_height * size.m_scale, size.m_width * size.m_scale, {0, 0, 0, 170}); //shadow
    auto contentFrame = m_screenGraphics.AddRectangle ({0.f, 0.f}, DrawPosition::Center, height, width, Colors::ghost);
    m_screenGraphics.AddRectangle ({0.f, 0.f}, DrawPosition::Center, height * 0.97, width * 0.98, Colors::darkestBlue);
    auto bbox = contentFrame->GetBoundingBox();
    float posX = 0;
    float posY = GraphicsHelper::ComputePosition (DrawPosition::Top, bbox).y;
    m_screenGraphics.AddText ({posX, posY + height * 0.17f}, DrawPosition::Center, "GAME OVER", height * 0.12, Colors::red);
    m_screenGraphics.AddText ({posX, posY + height * 0.32f}, DrawPosition::Center, "Your score:", height * 0.08, RAYWHITE);
    m_screenGraphics.AddText ({posX, posY + height * 0.47f}, DrawPosition::Center, std::to_string (score), height * 0.12, Colors::yellow);

    m_gameOverMenu = new Menu (height * 0.31, std::make_unique <ScreenCloseCommand> (this));
    m_gameOverMenu->SetColumnWidth (width * 0.45, width * 0.45);
    auto buttonContinue = std::make_unique <Button> ("Restart", width * 0.4, std::make_unique <GOSubScreenRestartCommand> (this));
    auto buttonExit = std::make_unique <Button> ("Continue", width * 0.4, std::make_unique <ScreenChangeCommand> (Screens::TETRIS_HIGHSCORES, this));
    m_gameOverMenu->AddRow (std::move (buttonContinue), std::move (buttonExit));
    m_screenGraphics.AddDrawableObject ({posX, posY + height * 0.6f}, DrawPosition::Top, m_gameOverMenu);

    m_inputLayer.AddAction (GAMEPAD_BUTTON_RIGHT_FACE_DOWN, KEY_ENTER, ActionType::PRESS, std::make_unique <MenuSelectCommand>());
    m_inputLayer.AddAction (GAMEPAD_BUTTON_LEFT_FACE_LEFT, KEY_LEFT, ActionType::PRESS, std::make_unique <MenuMoveLeftCommand>());
    m_inputLayer.AddAction (GAMEPAD_BUTTON_LEFT_FACE_RIGHT, KEY_RIGHT, ActionType::PRESS, std::make_unique <MenuMoveRightCommand>());

    m_inputHandler->PushInputLayer (&m_inputLayer);
    m_inputHandler->PushObject (m_gameOverMenu);

    m_screenGraphics.Translate (posCenter);
}

void ClassicTetrisGameScreen::GameOverSubScreen::NotifyGameReset()
{
    Notify (*this, Event::GAME_RESET);
}

ClassicTetrisGameScreen::GameOverSubScreen::~GameOverSubScreen()
{
    m_inputHandler->PopInputLayer();
    m_inputHandler->PopObject();
}

CTGHighScoresScreen::CTGHighScoresScreen (const ScreenSize& screenSize, HighScores scores, InputHandler* iHandler):
    Screen (iHandler)
{
    m_screenGraphics.AddRectangle ({0.0},
                                   DrawPosition::TopLeft,
                                   screenSize.m_height * screenSize.m_scale,
                                   screenSize.m_width * screenSize.m_scale,
                                   Colors::darkBlue);

    auto mainBBox = m_screenGraphics.GetBoundingBox();
    float posXmid = mainBBox.Width() / 2;
    float height = mainBBox.Height();

    m_screenGraphics.AddText ({posXmid, height * 0.05f}, DrawPosition::Top, "HIGHSCORES", height * 0.07f, RAYWHITE);

    float tableHeight = height * 0.6f;
    float tableWidth = mainBBox.Width() * 0.82f;
    float tableCellHeight = tableHeight / 10;

    auto table = new Table <3> (tableCellHeight);
    table->SetWidths ({tableWidth * 0.25f, tableWidth * 0.5f, tableWidth * 0.25f});

    auto idxHeader = new shapes::Text ("", tableCellHeight * 0.8f);
    idxHeader->SetColor (RAYWHITE);
    auto scoreHeader = new shapes::Text ("Score", tableCellHeight * 0.8f);
    scoreHeader->SetColor (RAYWHITE);
    auto linesHeader = new shapes::Text ("Lines", tableCellHeight * 0.8f);
    linesHeader->SetColor (RAYWHITE);
    table->AddRow ({idxHeader, scoreHeader, linesHeader});

    size_t idx = 1;
    for (const auto& record : scores.GetRecords()) {
        auto containerIdx = new DrawableContainer ();
        auto containerScore = new DrawableContainer ();
        auto containerLines = new DrawableContainer ();

        containerIdx->AddRectangle ({0.f, 0.f}, DrawPosition::Center, tableCellHeight * 0.9f, table->GetColWidth<0>(), Colors::blue_shade);
        containerScore->AddRectangle ({0.f, 0.f}, DrawPosition::Center, tableCellHeight * 0.9f, table->GetColWidth<1>(), Colors::blue_shade);
        containerLines->AddRectangle ({0.f, 0.f}, DrawPosition::Center, tableCellHeight * 0.9f, table->GetColWidth<2>(), Colors::blue_shade);
        if (!record.isNew) {
            containerIdx->AddText ({0.f, 0.f}, DrawPosition::Center, std::to_string (idx++), tableCellHeight * 0.8f, RAYWHITE);
            containerScore->AddText ({0.f, 0.f}, DrawPosition::Center, std::to_string (record.score), tableCellHeight * 0.8f, Colors::yellow);
            containerLines->AddText ({0.f, 0.f}, DrawPosition::Center, std::to_string (record.lines), tableCellHeight * 0.8f, Colors::green);
        } else {
            auto idxText = std::make_shared <shapes::Text> (std::to_string (idx++), tableCellHeight * 0.8f);
            auto scoreText = std::make_shared <shapes::Text> (std::to_string (record.score), tableCellHeight * 0.8f);
            auto linesText = std::make_shared <shapes::Text> (std::to_string (record.lines), tableCellHeight * 0.8f);
            idxText->SetColor (Colors::red);
            scoreText->SetColor (Colors::red);
            linesText->SetColor (Colors::red);


            auto CreateAnim = [] (std::shared_ptr <shapes::Text>& text, std::vector <Animation*>& anims) {
                auto animation = new Animation (text);
                animation->AddChangeColorAnimStep (60, RAYWHITE);
                animation->AddSetColorAnimStep (30, RAYWHITE);
                animation->AddChangeColorAnimStep (60, Colors::red);
                animation->AddSetColorAnimStep (30, Colors::red);
                animation->EnableLooping();
                animation->Play ();
                anims.push_back (animation);
                return animation;
            };

            auto idxAnimation = CreateAnim (idxText, m_anims);
            auto scoreAnimation = CreateAnim (scoreText, m_anims);
            auto linesAnimation = CreateAnim (linesText, m_anims);

            containerIdx->AddDrawableObject ({0.f, 0.f}, DrawPosition::Center, idxAnimation);
            containerScore->AddDrawableObject ({0.f, 0.f}, DrawPosition::Center, scoreAnimation);
            containerLines->AddDrawableObject ({0.f, 0.f}, DrawPosition::Center, linesAnimation);
        }

        table->AddRow ({containerIdx, containerScore, containerLines});
    }
    m_screenGraphics.AddDrawableObject ({posXmid, height * 0.14f}, DrawPosition::Top, table);

    m_menu = new Menu (height * 0.12f, std::make_unique <ScreenCloseCommand> (this));
    m_menu->SetColumnWidth (tableWidth);
    auto buttonContinue = std::make_unique <Button> ("Continue", tableWidth * 0.3f, std::make_unique <ScreenChangeCommand> (Screens::MAIN_MENU, this));
    m_menu->AddRow (std::move (buttonContinue));
    m_screenGraphics.AddDrawableObject ({posXmid, height * 0.835f}, DrawPosition::Top, m_menu);

    m_inputLayer.AddAction (GAMEPAD_BUTTON_RIGHT_FACE_DOWN, KEY_ENTER, ActionType::PRESS, std::make_unique <MenuSelectCommand> ());
    m_inputLayer.AddAction (GAMEPAD_BUTTON_LEFT_FACE_LEFT, KEY_LEFT, ActionType::PRESS, std::make_unique <MenuMoveLeftCommand> ());
    m_inputLayer.AddAction (GAMEPAD_BUTTON_LEFT_FACE_RIGHT, KEY_RIGHT, ActionType::PRESS, std::make_unique <MenuMoveRightCommand> ());

    m_inputHandler->PushInputLayer (&m_inputLayer);
    m_inputHandler->PushObject (m_menu);

}

void CTGHighScoresScreen::Tick()
{
    for (auto& elem : m_anims) {
        elem->Tick();
    }
    m_screenGraphics.Draw();
}

CTGHighScoresScreen::~CTGHighScoresScreen()
{
    m_inputHandler->PopInputLayer();
    m_inputHandler->PopObject();
}
