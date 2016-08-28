#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include "Subject.h"

#include <inttypes.h>

#include "Sensor.h"

typedef struct
{
	float position;
	float pressure;
} sensor_t;

class SensorManager : public Subject<sensor_t>
{
	public:
		SensorManager(Sensor * sensorPosition, Sensor * sensorPressure);
		~SensorManager();

		void triggerMeasures();
		void notify();

	private:
		Sensor * m_sensorPosition;
		Sensor * m_sensorPressure;

		sensor_t m_sensorData;

};

#endif // SENSOR_MANAGER_H