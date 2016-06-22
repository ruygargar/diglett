#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include "StateMachine.h"

#include "Screen.h"
#include "BundleBase.h"

#include "SensorManager.h"

typedef enum
{
	SCREEN_BUILD = 0,
	SCREEN_DATE,
	SCREEN_NEW_POINT,
	SCREEN_PROBING,
	SCREEN_MENU,
	SCREEN_TERMINATE,
	NUM_SCREENS,
} ScreenIndex_t;

class GuiManager
{
	public:
		GuiManager(SensorManager * model_sensors);
		~GuiManager();

		Event_t run();

		void createScreen(ScreenIndex_t);
		BundleBase * getBundle() { return m_bundle; };

	private:
		Screen * m_screen;
		Event_t m_event;

		SensorManager * m_model_sensors;
		BundleBase * m_bundle;
};

#endif // GUI_MANAGER_H