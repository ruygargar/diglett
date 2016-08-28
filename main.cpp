#include "Arduino.h"
#include "LiquidCrystal.h"

#include "StateMachine.h"

#include "DataManager.h"
#include "GuiManager.h"

#include "SensorAnalog.h"
#include "SensorManager.h"

#define POSITION_PIN 5
#define PRESSURE_PIN 10

#define MEASURES_TO_AVERAGE 10

extern "C" void __cxa_pure_virtual() { while (1); }

LiquidCrystal lcd(16, 17, 23, 25, 27, 29);

GuiManager * gui;
DataManager * data;
SensorManager * sensors;
SensorAnalog * position;
SensorAnalog * pressure;

int main(void)
{
	init();

	lcd.begin(20, 4);
	lcd.clear();

	position = new SensorAnalog(POSITION_PIN, MEASURES_TO_AVERAGE);
	pressure = new SensorAnalog(PRESSURE_PIN, MEASURES_TO_AVERAGE);
	sensors = new SensorManager(position, pressure);

	data = new DataManager(sensors);
	gui = new GuiManager(data, sensors);

	State_t state = STATE_INIT;
	Event_t event = EVENT_NONE;

	while (1)
	{
		sensors->triggerMeasures();
		event = gui->run();
		state = run_state(state, event);
	}

	return (0);
}