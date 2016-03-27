#include "GuiManager.h"

#include "SiteScreen.h"
#include "DateScreen.h"

#include <stddef.h>
#include "Logger.h"

GuiManager::GuiManager()
	: m_event(EVENT_NONE)
	, m_screen(NULL)
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

		case SCREEN_DATE:
		{
			m_screen = new DateScreen();
			break;
		}
	}
	logger_println("<- GuiManager::createScreen()");
}