#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

typedef enum
{
	STATE_INIT = 0,
	STATE_PAINT,
	STATE_CLICK,
	STATE_TERMINATE,
	NUM_STATES,
} State_t;

typedef enum
{
	EVENT_MOUSEMOVE,
	EVENT_KEYPRESS,
} Event_t;

typedef State_t State_func_t(Event_t event);

// State functions
State_t do_state_init(Event_t event);
State_t do_state_paint(Event_t event);
State_t do_state_click(Event_t event);
State_t do_state_terminate(Event_t event);

// State table
extern State_func_t * const state_table[NUM_STATES];

// State runner
State_t run_state(State_t current_state, Event_t event);

#endif // STATE_MACHINE_H