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
	private:
		typedef enum
		{
			INCREASING = 0,
			DECREASING
		} direction_t;

	public:
		SensorManager(Sensor * sensorPosition, Sensor * sensorPressure);
		~SensorManager();

		void init();
		void triggerMeasures();

	private:
		void notify();

		float roundData(float data, float precision);

		float processPosition(float data);
		float processPressure(float data);

	private:
		Sensor * m_sensorPosition;
		Sensor * m_sensorPressure;

		sensor_t m_sensorData;

		direction_t m_direction;

		float m_position;
		float m_maxPosition;
		float m_diffPosition;

		float m_pressure;
};

#endif // SENSOR_MANAGER_H