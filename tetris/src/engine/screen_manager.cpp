#include <engine/screen_manager.h>

#include <engine/event_timer_handler.h>
#include <engine/screen.h>
#include <tetris_game/classic_tetris_game_screen.h>
#include <tetris_game/title_screen.h>

ScreenManager::ScreenManager (const ScreenSize& screenSize):
    m_inputHandler (new InputHandler),
    m_screenSize (screenSize),
    m_currentState (Screens::TITLE),
    //m_currentScreen (new MainMenuScreen (m_inputHandler.get(), m_screenSize)),
    m_currentScreen (new TitleScreen (m_inputHandler.get(), m_screenSize)),
    m_bShouldClose (false)
{}

void ScreenManager::Tick()
 {
    m_inputHandler->Tick();
    EventTimerHandler::GetInstance().Tick();
    if (!m_currentScreen) {
            return;
    }
    if (m_currentScreen->IsActive()) {
        m_currentScreen->Tick();
        if (m_currentScreen->DoesWantToChangeScreen()) {
            switch (m_currentScreen->GetNextScreen())
            {
            case Screens::MAIN_MENU:
                m_currentState = Screens::MAIN_MENU;
                delete m_currentScreen;
                m_currentScreen = new MainMenuScreen (m_inputHandler.get(), m_screenSize);
                break;
            case Screens::TETRIS_GAME:
                m_currentState = Screens::TETRIS_GAME;
                delete m_currentScreen;
                m_currentScreen = new ClassicTetrisGameScreen (m_screenSize, m_inputHandler.get());
                break;
            case Screens::TETRIS_HIGHSCORES:
                if (auto CTGScreen = dynamic_cast <ClassicTetrisGameScreen*> (m_currentScreen)) {
                    m_currentState = Screens::TETRIS_HIGHSCORES;
                    auto scores = CTGScreen->GetGameHighScores();
                    delete m_currentScreen;
                    m_currentScreen = new CTGHighScoresScreen (m_screenSize, scores, m_inputHandler.get());
                }
                break;
            case Screens::SETTINGS:
            default:
                break;
            }
        }
    } else {
        switch (m_currentState)
        {
        case Screens::MAIN_MENU:
            m_bShouldClose = true;
            m_currentState = Screens::NONE;
            delete m_currentScreen;
            m_currentScreen = nullptr;
            break;
        case Screens::TETRIS_GAME:
        case Screens::SETTINGS:
            m_currentState = Screens::MAIN_MENU;
            delete m_currentScreen;
            m_currentScreen = new MainMenuScreen (m_inputHandler.get(), m_screenSize);
            break;
        default:
            break;
        }
    }
}

ScreenManager::~ScreenManager()
{
    if (m_currentScreen) {
        delete m_currentScreen;
    }
}
