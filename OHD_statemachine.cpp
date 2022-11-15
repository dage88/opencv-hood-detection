#include "OHD_statemachine.hpp"

void OHD_StateMachine::onEntry()
{
    m_event = OHD_EVENT_NONE; // For now ok, as we do not have events coming from outside the statemachine.
}

void OHD_StateMachine::onExit()
{
    if (m_event != OHD_EVENT_NONE)
    {
        switch (m_state)
        {
        case OHD_STATE_UNINITIALIZED:
            if (m_event == OHD_EVENT_RUN_REQUEST)
            {
                m_state = OHD_STATE_STARTUP;
            }
            break;

        case OHD_STATE_STARTUP:
            if (m_event == OHD_EVENT_STARTUP_SUCCESSFUL)
            {
                m_state = OHD_STATE_RUNNING;
            }
            break;

        case OHD_STATE_RUNNING:
            if (m_event == OHD_EVENT_ERROR)
            {
                m_state = OHD_STATE_ERROR;
            }
            break;

        case OHD_STATE_ERROR:
            // No more transitions

        default:
            break;
        }
    }
}

OHD_event_t OHD_StateMachine::getEvent()
{
    return m_event;
}

OHD_state_t OHD_StateMachine::getState()
{
    return m_state;
}

void OHD_StateMachine::setEvent(OHD_event_t event)
{
    m_event = event;
}

void OHD_StateMachine::setState(OHD_state_t state)
{
    m_state = state;
}
