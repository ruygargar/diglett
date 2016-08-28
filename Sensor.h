#ifndef SENSOR_H
#define SENSOR_H

class Sensor
{
	public:
		Sensor() {};
		virtual ~Sensor() {};

		virtual void init() = 0;
		virtual void measure() = 0;
		virtual bool isNewDataAvailable() = 0;
		virtual float getData() = 0;
};

#endif // SENSOR_H