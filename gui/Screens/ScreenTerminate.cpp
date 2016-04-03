#include "ScreenTerminate.h"

#include "LiquidCrystal.h"
extern LiquidCrystal lcd;

ScreenTerminate::ScreenTerminate()
{
	m_text = new Text(0, 0, "Desconecte la alimentacion\0");
}

ScreenTerminate::~ScreenTerminate()
{
	delete m_text;
}

void ScreenTerminate::control()
{}

Event_t ScreenTerminate::compute()
{
	return EVENT_NONE;
}

void ScreenTerminate::draw()
{
	lcd.clear();
	m_text->draw();
}