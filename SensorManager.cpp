#include "SensorManager.h"

#include <math.h>
#include <stddef.h>

#include "Arduino.h"

SensorManager::SensorManager(Sensor * sensorPosition, Sensor * sensorPressure)
	: Subject<sensor_t>()
	, m_sensorPosition{sensorPosition}
	, m_sensorPressure{sensorPressure}
	, m_sensorData{0.0, 0.0}
	, m_direction{DECREASING}
	, m_position{0.0}
	, m_maxPosition{0.0}
	, m_diffPosition{0.0}
	, m_pressure{0.0}
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
		m_position = roundData(processPosition(m_sensorPosition->getData()), 0.005);
		m_pressure = roundData(processPressure(m_sensorPressure->getData()), 0.1);

		if (m_direction == INCREASING)
		{
			if (m_position > m_maxPosition)
			{
				m_diffPosition = m_position - m_maxPosition;
				m_maxPosition += m_diffPosition;
				m_sensorData.position += m_diffPosition;
			}

			if (m_position == 0.5)
			{
				m_direction = DECREASING;
			}
		}
		else
		{
			if (m_position == 0.0)
			{
				m_maxPosition = 0.0;
				m_direction = INCREASING;
			}
		}
		m_sensorData.pressure = m_pressure;

		notify();
	}
}

void SensorManager::init()
{
	m_sensorPosition->init();
	m_sensorPressure->init();

	m_sensorData.position = 0.0;
	m_sensorData.pressure = 0.0;

	m_direction = DECREASING;
	m_position = 0.0;
	m_maxPosition = 0.0;
	m_diffPosition = 0.0;
	m_pressure = 0.0;
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

float SensorManager::roundData(float data, float precision)
{
	float roundedFactor = round(data / precision);
	float roundedData = roundedFactor * precision;
	return roundedData;
}

float SensorManager::processPosition(float data)
{
	float meters = (data / 1023.0) * 0.5;
	return meters;
}

float SensorManager::processPressure(float data)
{
	return data;
}