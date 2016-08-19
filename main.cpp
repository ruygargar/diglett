#include "Arduino.h"
#include "LiquidCrystal.h"

#include "StateMachine.h"

#include "GuiManager.h"
#include "SensorManager.h"
#include "DataManager.h"

extern "C" void __cxa_pure_virtual() { while (1); }

LiquidCrystal lcd(16, 17, 23, 25, 27, 29);

GuiManager * gui;
DataManager * data;
SensorManager * sensors;

int main(void)
{
	init();

	lcd.begin(20, 4);
	lcd.clear();

	sensors = new SensorManager();
	data = new DataManager(sensors);
	gui = new GuiManager(data, sensors);

	State_t state = STATE_INIT;
	Event_t event = EVENT_NONE;

	while (1)
	{
		sensors->readData();
		event = gui->run();
		state = run_state(state, event);
	}

	return (0);
}