#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

typedef enum
{
	STATE_INIT = 0,
	STATE_NEW_BUILD,
	STATE_NEW_POINT,
	STATE_PROBING,
	STATE_MENU,
	STATE_TERMINATE,
	NUM_STATES
} State_t;

typedef enum
{
	EVENT_NONE,
	EVENT_NEXT_PAGE,
	EVENT_JUMP_PROBING,
	EVENT_JUMP_NEW_POINT,
	EVENT_JUMP_NEW_BUILD,
	EVENT_JUMP_TERMINATE
} Event_t;

typedef State_t State_func_t(Event_t event);

// State functions
State_t do_state_init(Event_t event);
State_t do_state_new_build(Event_t event);
State_t do_state_new_point(Event_t event);
State_t do_state_probing(Event_t);
State_t do_state_menu(Event_t);
State_t do_state_terminate(Event_t event);

// State table
extern State_func_t * const state_table[NUM_STATES];

// State runner
State_t run_state(State_t current_state, Event_t event);

#endif // STATE_MACHINE_H