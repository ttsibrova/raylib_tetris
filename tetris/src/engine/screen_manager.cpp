#include <engine/screen_manager.h>

#include <engine/screen.h>
#include <tetris_game/classic_tetris_game_screen.h>

ScreenManager::ScreenManager (const ScreenSize& screenSize):
    m_inputHandler (new InputHandler),
    m_screenSize (screenSize),
    m_currentState (Screens::MAIN_MENU),
    m_currentScreen (new MainMenuScreen (m_inputHandler.get(), m_screenSize)),
    m_bShouldClose (false)
{}

void ScreenManager::Tick()
 {
    m_inputHandler->Tick();
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
