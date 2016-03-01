#include "Arduino.h"

int main()
{
	init();
	pinMode(13, OUTPUT);

	while (1) 
	{
		digitalWrite(13, HIGH);
	}

	return 0;
}