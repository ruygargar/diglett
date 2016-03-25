#include "Arduino.h"

//#include <stdio.h>
//#include <stdlib.h>

#include "Logger.h"
#include "Encoder.h"

//extern "C" void __cxa_pure_virtual() { while (1); }

Encoder * my_encoder;

int main(void)
{
	init();

	logger_init();

	while (1)
	{
		my_encoder = new Encoder();

		delay(5000);

		logger_println(my_encoder->getMovement());

		if (my_encoder->getClick())
		{
			logger_println("Button pushed");
		}
		else
		{
			logger_println("Button NOT pushed");
		}

		delete my_encoder;
				delay(5000);
	}

	return (0);
}