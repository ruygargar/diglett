#include "Arduino.h"

//#include <stdio.h>
//#include <stdlib.h>

#include "LiquidCrystal.h"

#include "Logger.h"
#include "Spinner.h"

#include "SiteScreen.h"

#include "StateMachine.h"

extern "C" void __cxa_pure_virtual() { while (1); }

LiquidCrystal lcd(16, 17, 23, 25, 27, 29);

SiteScreen * my_screen;

unsigned long time;
Event_t event = EVENT_NONE;

int main(void)
{
	init();
	lcd.begin(20, 4);
	lcd.clear();

	logger_init();

	while (1)
	{
		event = EVENT_NONE;
		lcd.clear();
		my_screen = new SiteScreen();

		time = millis() + 10000;
		while (event == EVENT_NONE)
		{
			my_screen->control();
			event = my_screen->compute();
			my_screen->draw();
		}

		delete my_screen;
		delay(10000);
	}

	return (0);
}