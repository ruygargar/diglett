#ifndef SENSOR_ANALOG_H
#define SENSOR_ANALOG_H

#include "Sensor.h"

#include <stdint.h>

class SensorAnalog : public Sensor
{
	public:
		SensorAnalog(uint8_t pin, uint8_t measuresPerAverage = 1);
		~SensorAnalog();

		void init();
		void measure();
		bool isNewDataAvailable();
		float getData();

	private:
		float convert(float raw);

	private:
		uint8_t m_analogPin;

		uint16_t m_rawData;
		uint16_t m_accumulatedRawData;

		uint8_t m_measuresTaken;
		uint8_t m_measuresPerAverage;

		bool m_newDataAvailable;

		float m_data;
};

#endif // SENSOR_ANALOG_H