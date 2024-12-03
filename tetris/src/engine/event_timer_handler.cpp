#include <engine/event_timer_handler.h>

EventTimerHandler& EventTimerHandler::GetInstance()
{
    static EventTimerHandler instance;
    return instance;
}

void EventTimerHandler::AddTimer (float time, CommandWithContext* command)
{
    m_timers.emplace_back (time, command);
}

void EventTimerHandler::Update()
{
    for (auto it = m_timers.begin(); it != m_timers.end();) {
        it->Update();
        if (it->IsExpired()) {
            it = m_timers.erase (it);
        } else 
            it++;
    }
}
