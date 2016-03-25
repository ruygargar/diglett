#include "Arduino.h"

//#include <stdio.h>
//#include <stdlib.h>

#include "LiquidCrystal.h"

#include "Logger.h"
#include "Spinner.h"

extern "C" void __cxa_pure_virtual() { while (1); }

LiquidCrystal lcd(16, 17, 23, 25, 27, 29);

Spinner * my_spinner;
unsigned long time;
char character;

int main(void)
{
	init();
	lcd.begin(20, 4);
	lcd.clear();

	logger_init();

	while (1)
	{
		my_spinner = new Spinner(3, SPINNERTYPE_ALPHANUMERIC);

		time = millis() + 10000;
		while (time > millis())
		{
			my_spinner->control();
			my_spinner->draw();

			character = my_spinner->character();
			if (character != 0x00)
			{
				logger_print("-------------->");
				logger_println(character);
			}

			delay(500);
		}

		delete my_spinner;
		delay(10000);
	}

	return (0);
}