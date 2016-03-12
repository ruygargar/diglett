#include <stdio.h>

#include "StateMachine.h"

State_func_t * const state_table[NUM_STATES] =
{
	do_state_init,
	do_state_paint,
	do_state_click,
	do_state_terminate,
};

State_t run_state(State_t current_state, Event_t event)
{
	return state_table[current_state](event);
}

State_t do_state_init(Event_t event)
{
	if (event == EVENT_MOUSEMOVE)
		return STATE_PAINT;
	
	return STATE_INIT;
}

State_t do_state_paint(Event_t event)
{
	if (event == EVENT_KEYPRESS)
		return STATE_CLICK;

	return STATE_PAINT;
}

State_t do_state_click(Event_t event)
{
	if (event == EVENT_KEYPRESS)
		return STATE_TERMINATE;

	return STATE_CLICK;
}

State_t do_state_terminate(Event_t event)
{
	return STATE_TERMINATE;
}