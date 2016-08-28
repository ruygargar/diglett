#include "SensorManager.h"

#include <stddef.h>

#include "Arduino.h"

#include "Logger.h"

SensorManager::SensorManager(Sensor * sensorPosition, Sensor * sensorPressure)
	: Subject<sensor_t>()
	, m_sensorPosition{sensorPosition}
	, m_sensorPressure{sensorPressure}
	, m_sensorData{0.0, 0.0}
{
	m_sensorPosition->init();
	m_sensorPressure->init();
}

SensorManager::~SensorManager()
{}

void SensorManager::triggerMeasures()
{
	m_sensorPosition->measure();
	m_sensorPressure->measure();

	if ( m_sensorPosition->isNewDataAvailable() ||
		 m_sensorPressure->isNewDataAvailable() )
	{
		m_sensorData.position = m_sensorPosition->getData();
		m_sensorData.pressure = m_sensorPressure->getData();
		notify();
	}
}

void SensorManager::notify()
{
	if (this->m_observer_gui != NULL)
	{
		this->m_observer_gui->update(m_sensorData);
	}

	if (this->m_observer_logger != NULL)
	{
		this->m_observer_logger->update(m_sensorData);
	}
}