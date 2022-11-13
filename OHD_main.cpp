#include <iostream>

#include "OHD_statemachine.hpp"
#include "OHD_types.hpp"

int main()
{
    OHD_StateMachine sm;
    event_t event = EVENT_INITIALIZE_REQUEST;
    int counter = 0;

    sm.OHD_StateMachine::ProcessEvent(event);

    while (true)
    {
        counter++;
        if (counter == 0)
        {
            std::cout << "Overflow.";
        }
    };

    std::cout << "main end.";
    return 0;
}