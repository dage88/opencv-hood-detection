#ifndef OHD_STATEMACHINE_HPP
#define OHD_STATEMACHINE_HPP

#include "OHD_types.hpp"

class OHD_StateMachine
{
public:
    OHD_StateMachine() : m_state(OHD_STATE_UNINITIALIZED),
                         m_event(OHD_EVENT_NONE){};
    OHD_StateMachine(OHD_state_t state, OHD_event_t event) : m_state(state),
                                                                 m_event(event){};
    virtual ~OHD_StateMachine(){};

    virtual OHD_event_t getEvent();
    virtual OHD_state_t getState();

    virtual void setEvent(OHD_event_t event);
    virtual void setState(OHD_state_t state);

    virtual void onEntry();
    virtual void onExit();

private:
    OHD_state_t m_state;
    OHD_event_t m_event;
    bool m_acceptEvent = true;

protected:
};

#endif /* OHD_STATEMACHINE_HPP */