#include "ScreenMenu.h"

#include "LiquidCrystal.h"
extern LiquidCrystal lcd;

ScreenMenu::ScreenMenu()
{
	m_text_item_0 = new Text(0, 2, "Continuar\0");
	m_text_item_1 = new Text(1, 2, "Nuevo punto\0");
	m_text_item_2 = new Text(2, 2, "Nueva obra\0");
	m_text_item_3 = new Text(3, 2, "Terminar\0");

	m_selector = new Selector(0, 4);
}

ScreenMenu::~ScreenMenu()
{
	delete m_text_item_0;
	delete m_text_item_1;
	delete m_text_item_2;
	delete m_text_item_3;
	delete m_selector;
}

void ScreenMenu::control()
{
	m_selector->control();
}

Event_t ScreenMenu::compute()
{
	uint8_t item = m_selector->item();
	switch (item)
	{
		case 0:
		{
			return EVENT_JUMP_PROBING;
		}
		case 1:
		{
			return EVENT_JUMP_NEW_POINT;
		}
		case 2:
		{
			return EVENT_JUMP_NEW_BUILD;
		}
		case 3:
		{
			return EVENT_JUMP_TERMINATE;
		}
	}

	return EVENT_NONE;
}

void ScreenMenu::draw()
{
	lcd.clear();
	
	m_text_item_0->draw();
	m_text_item_1->draw();
	m_text_item_2->draw();
	m_text_item_3->draw();
	m_selector->draw();
}