#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include "StateMachine.h"
#include "Screen.h"

typedef enum
{
	SCREEN_BUILD = 0,
	SCREEN_DATE,
	NUM_SCREENS,
} ScreenIndex_t;

class GuiManager
{
	public:
		GuiManager();
		~GuiManager();

		Event_t run();

		void createScreen(ScreenIndex_t);

	private:
		Screen * m_screen;
		Event_t m_event;
};

#endif // GUI_MANAGER_H