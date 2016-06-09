#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include "Subject.h"

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
		sensor_t m_sensor;
};

#endif // SENSOR_MANAGER_H