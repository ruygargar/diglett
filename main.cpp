#include "Arduino.h"

#include "HardwareSerial.h"
#include "SPI.h"
#include "SD.h"

int main()
{
	init();
	pinMode(13, OUTPUT);
	Serial.begin(115200);

	Serial.println("Serial initialized.");

	Serial.print("Initializing SD card...");
	if (!SD.begin())
	{
		Serial.println("Card failed, or not present");
	}
	else
	{
		Serial.println(" initialized.");

		if (SD.exists("/TestFile.txt"))
		{
			SD.remove("/testFile.txt");
		}

		Serial.print("Writing file /TestFile.txt...");
		File myFile = SD.open("/TestFile.txt", FILE_WRITE);
		myFile.write("This is a sample text!\r\n");
		myFile.flush();
		myFile.close();
		Serial.println(" done");

		Serial.println("Reading the file /TestFile.txt:");
		File myReadyFile = SD.open("/TestFile.txt", FILE_READ);
		for (uint32_t i = 0; i < myReadyFile.size(); i++)
		{
			Serial.print((char)myReadyFile.read());
		}
		myReadyFile.close();
	}

	while (1) 
	{
		digitalWrite(13, HIGH);
		delay(1000);
		digitalWrite(13, LOW);
		delay(1000);
	}

	return 0;
}