#include "Arduino.h"
#include "HardwareSerial.h"

#include "SPI.h"
#include "SD.h"

#include "LiquidCrystal.h"

#include "Encoder.h"

int main()
{
	init();
	pinMode(13, OUTPUT);
	Serial.begin(115200);

	Serial.println("Serial initialized.");

	Serial.print("Initializing LCD... ");
	LiquidCrystal lcd(16, 17, 23, 25, 27, 29);
	lcd.begin(20, 4);
	lcd.clear();
	Serial.println( "done");


	Serial.print("Initializing spinner... ");
	Encoder Spinner;
	Spinner.init();
	Serial.println( "done");

	while (1) 
	{
		digitalWrite(13, HIGH);
		delay(1000);
		digitalWrite(13, LOW);
		delay(1000);
		Serial.print("Encoder value: ");
		Serial.println(Spinner.getMovement());
	}

	return 0;
}