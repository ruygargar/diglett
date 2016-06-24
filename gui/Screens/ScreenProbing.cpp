#include <stdlib.h>

#include "ScreenProbing.h"
#include "LiquidCrystal.h"

extern LiquidCrystal lcd;

ScreenProbing::ScreenProbing(Subject<sensor_t> * model)
	: Observer<sensor_t>(model)
{
	m_text_distance = new Text(0, 0, "Distancia [m]:\0");
	m_text_distance_value = new Textbox(0, 15, 6);
	m_text_pressure = new Text(1, 0, "Presion [bar]:");
	m_text_pressure_value = new Textbox(1, 15, 6);
	m_text_menu = new Text(3, 0, "Pulse para volver\0");

	m_button = new Button();
}

ScreenProbing::~ScreenProbing()
{
	delete m_text_distance;
	delete m_text_distance_value;
	delete m_text_pressure;
	delete m_text_pressure_value;
	delete m_text_menu;

	delete m_button;
}

void ScreenProbing::control()
{
	m_button->control();
}

Event_t ScreenProbing::compute()
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

void ScreenProbing::draw()
{
	lcd.clear();
	m_text_distance->draw();
	m_text_distance_value->draw();
	m_text_pressure->draw();
	m_text_pressure_value->draw();
	m_text_menu->draw();
}

void ScreenProbing::update(sensor_t value)
{
	char position[6] = {"\0"};
	dtostrf(value.position, 4, 3, position);
	char pressure[6] = {"\0"};
	dtostrf(value.pressure, 4, 1, pressure);

	m_text_distance_value->flush();
	m_text_distance_value->pushString(position);

	m_text_pressure_value->flush();
	m_text_pressure_value->pushString(pressure);
}