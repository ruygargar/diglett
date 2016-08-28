#include "SensorAnalog.h"

#include "Arduino.h"

SensorAnalog::SensorAnalog(uint8_t pin, uint8_t measuresPerAverage)
	: m_analogPin{pin}
	, m_rawData{0}
	, m_accumulatedRawData{0}
	, m_measuresTaken{0}
	, m_measuresPerAverage{measuresPerAverage}
	, m_newDataAvailable{false}
	, m_data{0.0}
{}

SensorAnalog::~SensorAnalog()
{}

void SensorAnalog::init()
{}

void SensorAnalog::measure()
{
	m_rawData = analogRead(m_analogPin);
	m_accumulatedRawData += m_rawData;
	m_measuresTaken++;

	if (m_measuresTaken % m_measuresPerAverage == 0)
	{
		float meanRawData = ( (float) m_accumulatedRawData / (float) m_measuresPerAverage);
		m_data = convert(meanRawData);
		m_newDataAvailable = true;

		m_accumulatedRawData = 0;
		m_measuresTaken = 0;
	}
}

bool SensorAnalog::isNewDataAvailable()
{
	return m_newDataAvailable;
}

float SensorAnalog::getData()
{
	m_newDataAvailable = false;
	return m_data;
}

float SensorAnalog::convert(float raw)
{
	return raw;
}