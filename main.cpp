#include "Arduino.h"
#include "HardwareSerial.h"

#include <stdio.h>
#include <stdlib.h>

#include "StateMachine.h"

int main( void )
{
	init();

	Serial.begin(115200);

	State_t state = STATE_INIT;
	Event_t event;

	while (state != STATE_TERMINATE)
	{
		Serial.print("State: ");
		if (state == STATE_INIT)
		{
			Serial.println("STATE_INIT");
		}
		if (state == STATE_PAINT)
		{
			Serial.println("STATE_PAINT");
		}
		if (state == STATE_CLICK)
		{
			Serial.println("STATE_CLICK");
		}
		if (state == STATE_TERMINATE)
		{
			Serial.println("STATE_TERMINATE");
		}
		Serial.flush();

		while ( !(Serial.available() > 0) )
		{
			delay(100);
		}

		char input[2];
		input[0] = Serial.read();
		input[1] = '\0';
		event = (Event_t)(atoi(input));

		Serial.print("Event: ");
		if (event == EVENT_KEYPRESS)
			Serial.println("EVENT_KEYPRESS");
		if (event == EVENT_MOUSEMOVE)
			Serial.println("EVENT_MOUSEMOVE");
		Serial.flush();

		state = run_state(state, event);
	}

	while (1) {}

	return 0;
}