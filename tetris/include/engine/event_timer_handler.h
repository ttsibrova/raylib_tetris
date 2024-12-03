#pragma once
#include <engine/command.h>
#include <engine/game_object.h>

#include <raylib/raylib.h>

#include <memory>
#include <vector>

class Timer: public GameObject
{
public:
    Timer (float time, CommandWithContext* command):
        m_bIsExpired (false),
        m_time (time),
        m_timeStart (GetTime()),
        m_command (command)
    {}

    bool IsExpired() { return m_bIsExpired; }

    virtual void Update() override {
        if (GetTime() - m_timeStart > m_time) {
            m_command->ExecuteContext();
            m_bIsExpired = true;
        }
    }

private:
    bool                m_bIsExpired;
    float               m_time;
    float               m_timeStart;
    CommandWithContext* m_command;
};



class EventTimerHandler: public GameObject
{
public:
    static EventTimerHandler& GetInstance();

    void AddTimer (float time, CommandWithContext* command);

    virtual void Update() override;

private:
    EventTimerHandler(){}

private:
    std::vector <Timer> m_timers;
};

