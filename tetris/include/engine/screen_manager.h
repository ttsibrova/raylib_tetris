#pragma once
#include <engine/input_handler.h>
#include <engine/screen.h>
#include <engine/screen_properties.h>

class ScreenManager : public GameObject
{
public:
    ScreenManager (const ScreenSize& screenSize);

    virtual void Update() override;
    bool ShouldClose() { return m_bShouldClose; }

private:
    Screen* CurrentScreen() { return m_screenStack.top().get(); }
    template <typename ScreenType, typename ... Args>
    void ReplaceScreen (Args ... args) {
        m_screenStack.pop();
        m_screenStack.push (std::move (std::make_unique <ScreenType> (args...)));
    }

private:
    ScreenSize                            m_screenSize;
    Screens                               m_currentState;
    std::stack <std::unique_ptr <Screen>> m_screenStack;
    bool                                  m_bShouldClose;
};

