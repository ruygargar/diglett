#include "ScreenPoint.h"

#include "LiquidCrystal.h"
extern LiquidCrystal lcd;

ScreenPoint::ScreenPoint()
{
	m_text_point = new Text(0, 0, "Punto 1:\0");
	m_text_instructions = new Text(2, 0, "Pulse para comenzar\0");
	m_button = new Button();
}

ScreenPoint::~ScreenPoint()
{
	delete m_text_point;
	delete m_text_instructions;
	delete m_button;
}

void ScreenPoint::control()
{
	m_button->control();
}

Event_t ScreenPoint::compute()
{
	if (m_button->isPushed())
	{
		return EVENT_NEXT_PAGE;
	}
	else
	{
		return EVENT_NONE;
	}
}

void ScreenPoint::draw()
{
	lcd.clear();
	m_text_point->draw();
	m_text_instructions->draw();
}