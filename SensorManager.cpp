#include "SensorManager.h"

#include <stddef.h>

SensorManager::SensorManager()
	: Subject<sensor_t>()
	, m_sensor{0.0f, 1.0f}
{}

SensorManager::~SensorManager()
{}

void SensorManager::readData()
{
	m_sensor.position += 0.001;
	if (m_sensor.position > 10)
	{
		m_sensor.position -= 10;
	}

	m_sensor.pressure += 0.332;
	if (m_sensor.pressure > 1000)
	{
		m_sensor.pressure -= 999;
	}

	notify();
}

void SensorManager::notify()
{
	if (this->m_observer != NULL)
	{
		this->m_observer->update(m_sensor);
	}
}