#include "SensorManager.h"

#include <stddef.h>

#include "Arduino.h"

#include "Logger.h"

#define POSITION_PIN 5
#define PRESSURE_PIN 10

#define MEASURES_TO_AVERAGE 10

SensorManager::SensorManager()
	: Subject<sensor_t>()
	, m_sensor{0.0f, 0.0f}
	, m_measures_to_average{MEASURES_TO_AVERAGE}
	, m_measure_number{0}
	, m_acc_position{0}
	, m_acc_pressure{0}
{}

SensorManager::~SensorManager()
{}

void SensorManager::readData()
{
	uint16_t rawPosition = analogRead(POSITION_PIN);
	uint16_t rawPressure = analogRead(PRESSURE_PIN);

	m_acc_position += rawPosition;
	m_acc_pressure += rawPressure;
	m_measure_number++;

	if (m_measure_number >= m_measures_to_average)
	{
		float meanPosition = ((float) m_acc_position) / m_measures_to_average;
		float meanPressure = ((float) m_acc_pressure) / m_measures_to_average;

		m_sensor.position = meanPosition * ((0.5) / (1023.0)) + 0.0;
		m_sensor.pressure = meanPressure * ((250.0) / (1023.0)) + 0.0;
		resetCurrentMean();

		notify();
	}
}

void SensorManager::notify()
{
	if (this->m_observer_gui != NULL)
	{
		this->m_observer_gui->update(m_sensor);
	}

	if (this->m_observer_logger != NULL)
	{
		this->m_observer_logger->update(m_sensor);
	}
}

void SensorManager::resetCurrentMean()
{
	m_acc_position = 0;
	m_acc_pressure = 0;
	m_measure_number = 0;
}