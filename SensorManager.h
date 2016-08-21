#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include "Subject.h"

#include <inttypes.h>

typedef struct
{
	float position;
	float pressure;
} sensor_t;

class SensorManager : public Subject<sensor_t>
{
	public:
		SensorManager();
		~SensorManager();

		void readData();
		void notify();

	private:
		void resetCurrentMean();

	private:
		sensor_t m_sensor;

		uint8_t m_measures_to_average;
		uint8_t m_measure_number;

		uint16_t m_acc_position;
		uint16_t m_acc_pressure;
};

#endif // SENSOR_MANAGER_H