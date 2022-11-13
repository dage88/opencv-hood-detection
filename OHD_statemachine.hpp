#ifndef OHD_STATEMACHINE_HPP
#define OHD_STATEMACHINE_HPP

#include "OHD_types.hpp"

class OHD_StateMachine
{
public:
    OHD_StateMachine() : m_state(STATE_UNINITIALIZED), m_lastEvent(EVENT_NONE){};
    OHD_StateMachine(state_t state, event_t lastEvent)
        : m_state(state), m_lastEvent(lastEvent){};
    virtual ~OHD_StateMachine(){};

    virtual event_t getIncomingEvent();
    virtual bool ProcessEvent(event_t event);

private:
    state_t m_state;
    event_t m_incomingEvent;
    event_t m_lastEvent;
    bool m_acceptEvent = true;

protected:
};

#endif /* OHD_STATEMACHINE_HPP */