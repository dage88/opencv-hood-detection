#ifndef OHD_TYPES_HPP
#define OHD_TYPES_HPP

typedef enum
{
    STATE_UNDEFINED = 0,
    STATE_UNINITIALIZED,
    STATE_INITIALIZED
} state_t;

typedef enum
{
    EVENT_UNDEFINED = 0,
    EVENT_NONE,
    EVENT_INITIALIZE_REQUEST
} event_t;

#endif /* OHD_TYPES_HPP */