#pragma once
#include <engine/game_object.h>

class Command
{
public:
    virtual ~Command() {}
    virtual bool Execute (Object* obj) = 0;
};

class CommandWithContext: public Command
{
public:
    CommandWithContext (Object* contextObj):
        m_contextObj (contextObj)
    {}

    bool ExecuteContext() { return Execute (m_contextObj); }

private:
    Object* m_contextObj;
};
