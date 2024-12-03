#include <engine/screen_manager.h>

#include <engine/event_timer_handler.h>
#include <engine/screen.h>
#include <tetris_game/classic_tetris_game_screen.h>
#include <tetris_game/title_screen.h>

ScreenManager::ScreenManager (const ScreenSize& screenSize):
    m_screenSize (screenSize),
    m_currentState (Screens::TITLE),
    m_bShouldClose (false)
{
    m_screenStack.emplace (std::make_unique <TitleScreen> (screenSize));
}

void ScreenManager::Update()
 {
    InputHandler::GlobalInstance().Update();
    EventTimerHandler::GetInstance().Update();
    if (m_screenStack.empty()) {
            return;
    }
    if (CurrentScreen()->IsActive()) {
        CurrentScreen()->Update();
        if (CurrentScreen()->DoesWantToChangeScreen()) {
            switch (CurrentScreen()->GetNextScreen())
            {
            case Screens::MAIN_MENU:
                m_currentState = Screens::MAIN_MENU;
                ReplaceScreen <MainMenuScreen> (m_screenSize);
                break;
            case Screens::TETRIS_GAME:
                m_currentState = Screens::TETRIS_GAME;
                ReplaceScreen <ClassicTetrisGameScreen> (m_screenSize);
                break;
            case Screens::TETRIS_HIGHSCORES:
                if (auto CTGScreen = dynamic_cast <ClassicTetrisGameScreen*> (CurrentScreen())) {
                    m_currentState = Screens::TETRIS_HIGHSCORES;
                    auto scores = CTGScreen->GetGameHighScores();
                    ReplaceScreen <CTGHighScoresScreen> (m_screenSize, scores);
                }
                break;
            case Screens::TITLE:
                m_currentState = Screens::TITLE;
                ReplaceScreen <TitleScreen> (m_screenSize);
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
            m_screenStack.pop();
            break;
        case Screens::TETRIS_GAME:
        case Screens::SETTINGS:
            m_currentState = Screens::MAIN_MENU;
            ReplaceScreen <MainMenuScreen> (m_screenSize);
            break;
        default:
            break;
        }
    }
}

