#include <stdio.h>

#include "StateMachine.h"
#include "GuiManager.h"
#include "DataManager.h"

#include "BundleCharPtr.h"

extern GuiManager * gui;
extern DataManager * data;

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
		data->resetPointNumber();
		gui->createScreen(SCREEN_NEW_POINT);

		BundleCharPtr * bundle = (BundleCharPtr *) gui->getBundle();
		if (bundle != NULL)
		{
			data->newBuild(bundle->get());
		}

		return STATE_NEW_POINT;
	}

	return STATE_NEW_BUILD;
}

State_t do_state_new_point(Event_t event)
{
	if (event == EVENT_NEXT_PAGE)
	{
		data->newProbingPoint();
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
		data->incrementPointNumber();
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
		data->terminate();
		return STATE_TERMINATE;
	}
	return STATE_MENU;
}

State_t do_state_terminate(Event_t event)
{
	return STATE_TERMINATE;
}