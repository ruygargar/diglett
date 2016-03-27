#include <stdio.h>

#include "StateMachine.h"
#include "GuiManager.h"

#include "Logger.h"

extern GuiManager * gui;


State_func_t * const state_table[NUM_STATES] =
{
	do_state_init,
	do_state_build,
	do_state_date,
	do_state_terminate
};

State_t run_state(State_t current_state, Event_t event)
{
	logger_println("-> run_state()");
	logger_print("State: ");
	logger_println((int) current_state);
	logger_print("Event: ");
	logger_println((int) event);
	logger_println("<- run_state()");
	return state_table[current_state](event);
}

State_t do_state_init(Event_t event)
{
	gui->createScreen(SCREEN_BUILD);
	return STATE_BUILD;
}

State_t do_state_build(Event_t event)
{
	if (event == EVENT_NEXT_PAGE)
	{
		gui->createScreen(SCREEN_DATE);
		return STATE_DATE;
	}

	return STATE_BUILD;
}

State_t do_state_date(Event_t event)
{
	if (event == EVENT_NEXT_PAGE)
	{
		gui->createScreen(SCREEN_BUILD);
		return STATE_BUILD;
	}

	return STATE_DATE;
}

State_t do_state_terminate(Event_t event)
{
	return STATE_TERMINATE;
}