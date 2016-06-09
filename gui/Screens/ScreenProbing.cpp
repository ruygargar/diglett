#include <stdlib.h>

#include "ScreenProbing.h"
#include "LiquidCrystal.h"

#include "Logger.h"

extern LiquidCrystal lcd;

ScreenProbing::ScreenProbing(Subject<sensor_t> * model)
	: Observer<sensor_t>(model)
{
	logger_println("-> ScreenProbing::ScreenProbing()");
	m_text_distance = new Text(0, 0, "Distancia [m]:\0");
	m_text_distance_value = new Textbox(0, 15, 6);
	m_text_pressure = new Text(1, 0, "Presion [bar]:");
	m_text_pressure_value = new Textbox(1, 15, 6);
	m_text_menu = new Text(3, 0, "Pulse para volver\0");

	m_button = new Button();
	logger_println("<- ScreenProbing::ScreenProbing()");
}

ScreenProbing::~ScreenProbing()
{
	logger_println("-> ScreenProbing::~ScreenProbing()");
	delete m_text_distance;
	delete m_text_distance_value;
	delete m_text_pressure;
	delete m_text_pressure_value;
	delete m_text_menu;

	delete m_button;
	logger_println("<- ScreenProbing::~ScreenProbing()");
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
	logger_println("-> ScreenProbing::update()");

	logger_print("-- -- F Position: ");
	logger_println((float)value.position);
	logger_print("-- -- F Pressure: ");
	logger_println((float)value.pressure);

	char position[6] = {"\0"};
	dtostrf(value.position, 4, 3, position);
	char pressure[6] = {"\0"};
	dtostrf(value.pressure, 4, 1, pressure);

	logger_print("-- -- Position: ");
	logger_println(position);
	logger_print("-- -- Pressure: ");
	logger_println(pressure);

	m_text_distance_value->flush();
	m_text_distance_value->pushString(position);

	m_text_pressure_value->flush();
	m_text_pressure_value->pushString(pressure);
	logger_print("-- -- m_position: ");
	logger_println(m_text_distance_value->text());
	logger_print("-- -- m_pressure: ");
	logger_println(m_text_pressure_value->text());

	logger_println("<- ScreenProbing::update()");
}