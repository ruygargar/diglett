#include "Arduino.h"

//#include <stdio.h>
//#include <stdlib.h>

#include "LiquidCrystal.h"

#include "Logger.h"
#include "StateMachine.h"

#include "GuiManager.h"
#include "SensorManager.h"

extern "C" void __cxa_pure_virtual() { while (1); }

LiquidCrystal lcd(16, 17, 23, 25, 27, 29);

GuiManager * gui;
SensorManager * sensors;

int main(void)
{
	init();
	logger_init();

	lcd.begin(20, 4);
	lcd.clear();

	sensors = new SensorManager();
	gui = new GuiManager(sensors);

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