#include "Logger.h"

#include "Arduino.h"
#include "HardwareSerial.h"

void logger_init()
{
	Serial.begin(LOGGER_BAUDRATE);
	pinMode(LOGGER_LEDPIN, OUTPUT);
}



void logger_print(char * string)
{
	Serial.print(string);
	Serial.flush();
}

void logger_print(int number)
{
	Serial.print(number);
	Serial.flush();
}



void logger_println(char * string)
{
	Serial.println(string);
	Serial.flush();
}

void logger_println(int number)
{
	Serial.println(number);
	Serial.flush();
}



void logger_signal_on()
{
	digitalWrite(LOGGER_LEDPIN, 1);
}

void logger_signal_off()
{
	digitalWrite(LOGGER_LEDPIN, 0);
}