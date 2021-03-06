#include "DataManager.h"

#include <stddef.h>
#include <string.h>
#include "SD.h"

DataManager::DataManager(Subject<sensor_t> * model)
	: Observer<sensor_t>(model, OBSERVER_LOGGER)
	, m_file_number(1)
	, m_file(NULL)
	, m_data{0.0}
{
	m_directory_name = new char[21];
	m_file_name = new char[10];
	memset(m_directory_name, '\0', sizeof m_directory_name);
	memset(m_file_name, '\0', sizeof m_file_name);

	if (!SD.begin())
	{
		while (1) {}
	}
}

DataManager::~DataManager()
{
	delete m_directory_name;
	delete m_file_name;
}

void DataManager::newBuild(const char * name)
{
	char foldername[27] = { "\0" };
	sprintf(foldername, "/%s", name);

	uint8_t i = 1;
	while (SD.exists(foldername))
	{
		sprintf(foldername, "/%s(%d)", name, i);
		i++;
	}

	setFolder(foldername);
	SD.mkdir(m_directory_name);
}

void DataManager::newProbingPoint()
{
	close();

	char filename[10] = { "\0" };
	sprintf(filename, "Punto_%d", m_file_number);
	setFile(filename);
	m_data = 0.0;

	open();
}

void DataManager::terminate()
{
	close();
}

void DataManager::resetPointNumber()
{
	m_file_number = 1;
}

void DataManager::incrementPointNumber()
{
	m_file_number++;
}

uint16_t DataManager::getPointNumber()
{
	return m_file_number;
}

void DataManager::update(sensor_t value)
{
	if (m_file == NULL)
	{
		return;
	}

	if (filterData(value.position) == true)
	{
		char position[6] = {"\0"};
		dtostrf(value.position, 5, 3, position);
		char pressure[6] = {"\0"};
		dtostrf(value.pressure, 4, 1, pressure);

		m_file->write(position);
		m_file->write(",");
		m_file->write(pressure);
		m_file->write("\r\n");
		m_file->flush();
	}
}


void DataManager::setFolder(const char * directory)
{
	memset(m_directory_name, '\0', sizeof m_directory_name);
	strcpy(m_directory_name, directory);
}

void DataManager::setFile(const char * filename)
{
	memset(m_file_name, '\0', sizeof m_file_name);
	strcpy(m_file_name, filename);
}

void DataManager::open()
{
	char path[33] = { "\0" };
	sprintf(path, "%s/%s", m_directory_name, m_file_name);

	File * file = new File();
	*file = SD.open(path, FILE_WRITE);
	m_file = file;
}

void DataManager::close()
{
	if (m_file != NULL)
	{
		m_file->close();
		delete m_file;
	}
}

bool DataManager::filterData(float value)
{
	if (m_data < value)
	{
		m_data = value;
		return true;
	}
	return false;
}