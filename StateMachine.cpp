#include <stdio.h>

#include "StateMachine.h"
#include "GuiManager.h"

#include "Logger.h"

extern GuiManager * gui;


State_func_t * const state_table[NUM_STATES] =
{
	do_state_init,
	do_state_new_build,
	do_state_new_point,
	do_state_probing,
	do_state_menu,
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
	return STATE_NEW_BUILD;
}

State_t do_state_new_build(Event_t event)
{
	if (event == EVENT_NEXT_PAGE)
	{
		gui->createScreen(SCREEN_NEW_POINT);
		return STATE_NEW_POINT;
	}

	return STATE_NEW_BUILD;
}

State_t do_state_new_point(Event_t event)
{
	if (event == EVENT_NEXT_PAGE)
	{
		gui->createScreen(SCREEN_PROBING);
		return STATE_PROBING;
	}

	return STATE_NEW_POINT;
}

State_t do_state_probing(Event_t event)
{
	if (event == EVENT_NEXT_PAGE)
	{
		gui->createScreen(SCREEN_MENU);
		return STATE_MENU;
	}
	return STATE_PROBING;
}

State_t do_state_menu(Event_t event)
{
	if (event == EVENT_JUMP_PROBING)
	{
		gui->createScreen(SCREEN_PROBING);
		return STATE_PROBING;
	}
	else if (event == EVENT_JUMP_NEW_POINT)
	{
		gui->createScreen(SCREEN_NEW_POINT);
		return STATE_NEW_POINT;
	}
	else if (event == EVENT_JUMP_NEW_BUILD)
	{
		gui->createScreen(SCREEN_BUILD);
		return STATE_NEW_BUILD;
	}
	else if (event == EVENT_JUMP_TERMINATE)
	{
		gui->createScreen(SCREEN_TERMINATE);
		return STATE_TERMINATE;
	}
	return STATE_MENU;
}

State_t do_state_terminate(Event_t event)
{
	return STATE_TERMINATE;
}