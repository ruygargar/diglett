#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

typedef enum
{
	STATE_INIT = 0,
	STATE_BUILD = 1,
	STATE_DATE = 2,
	STATE_TERMINATE = 3,
	NUM_STATES
} State_t;

typedef enum
{
	EVENT_NONE,
	EVENT_NEXT_PAGE
} Event_t;

typedef State_t State_func_t(Event_t event);

// State functions
State_t do_state_init(Event_t event);
State_t do_state_build(Event_t event);
State_t do_state_date(Event_t event);
State_t do_state_terminate(Event_t event);

// State table
extern State_func_t * const state_table[NUM_STATES];

// State runner
State_t run_state(State_t current_state, Event_t event);

#endif // STATE_MACHINE_H