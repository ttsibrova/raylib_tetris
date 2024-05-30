#pragma once
#include <engine/game_object.h>
#include <functional/events.h>
#include <list>

template <typename E>
class IObserver
{
public:
    using Event = E;

    virtual void onNotify (const Object& obj, Event e) = 0;
};

using CTGSObserver = IObserver <ClassicTetrisGameScreenEvent>;


template <typename ObserverType>
class Subject
{
public:
    using Event = typename ObserverType::Event;

    void AddObserver (ObserverType* observer) {
        m_observers.push_back (observer);
    }
    void RemoveObserver (ObserverType* observer) {
        m_observers.remove (observer);
    }

protected:
    void Notify (const Object& obj, typename ObserverType::Event e) {
        for (auto observer : m_observers) {
            observer->onNotify (obj, e);
        }
    }

private:
    std::list <ObserverType*> m_observers;
};