#include "GuiManager.h"

#include "SiteScreen.h"
#include "DateScreen.h"
#include "ScreenMenu.h"
#include "ScreenPoint.h"
#include "ScreenProbing.h"
#include "ScreenTerminate.h"

#include <stddef.h>
#include "Logger.h"

GuiManager::GuiManager(SensorManager * model_sensors)
	: m_event(EVENT_NONE)
	, m_screen(NULL)
	, m_model_sensors(model_sensors)
{}

GuiManager::~GuiManager()
{
	if (m_screen != NULL)
	{
		delete m_screen;
	}
}

Event_t GuiManager::run()
{
	if (m_screen != NULL)
	{
		m_screen->control();
		m_event = m_screen->compute();
		m_screen->draw();
	
		return m_event;
	}

	return EVENT_NONE;
}

void GuiManager::createScreen(ScreenIndex_t id)
{
	logger_println("-> GuiManager::createScreen()");
	if (m_screen != NULL)
	{
		delete m_screen;
	}

	switch(id)
	{
		case SCREEN_BUILD:
		{
			m_screen = new SiteScreen();
			break;
		}

		case SCREEN_NEW_POINT:
		{
			m_screen = new ScreenPoint();
			break;
		}

		case SCREEN_PROBING:
		{
			m_screen = new ScreenProbing(m_model_sensors);
			break;
		}

		case SCREEN_MENU:
		{
			m_screen = new ScreenMenu();
			break;
		}
		case SCREEN_TERMINATE:
		{
			m_screen = new ScreenTerminate();
			break;
		}
	}
	logger_println("<- GuiManager::createScreen()");
}