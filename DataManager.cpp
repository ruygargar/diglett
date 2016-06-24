#include "DataManager.h"

#include <stddef.h>
#include <string.h>
#include "SD.h"

#include "Logger.h"

DataManager::DataManager()
	: m_file_number(1)
	, m_file(NULL)
	, m_distance(0.0)
	, m_pressure(1.0)
{
	logger_println("-> DataManager::DataManager()");
	m_directory_name = new char[21];
	m_file_name = new char[10];
	memset(m_directory_name, '\0', sizeof m_directory_name);
	memset(m_file_name, '\0', sizeof m_file_name);

	if (!SD.begin())
	{
		logger_println("Card failed, or not present");
		while (1) {}
	}
	logger_println("<- DataManager::DataManager()");
}

DataManager::~DataManager()
{
	delete m_directory_name;
	delete m_file_name;
}

void DataManager::newBuild(const char * name)
{
	logger_println("-> DataManager::newBuild()");
	
	// TODO: Check if folder already exists
	char foldername[27] = { "\0" };
	sprintf(foldername, "/%s", name);

	uint8_t i = 1;
	while (SD.exists(foldername))
	{
		logger_print("-- directory already exists: ");
		logger_println(foldername);
		sprintf(foldername, "/%s(%d)", name, i);
		i++;
	}

	setFolder(foldername);
	SD.mkdir(m_directory_name);
	logger_println("<- DataManager::newBuild()");
}

void DataManager::newProbingPoint()
{
	logger_println("-> DataManager::newProbingPoint()");
	close();

	char filename[10] = { "\0" };
	sprintf(filename, "Punto_%d", m_file_number);
	setFile(filename);

	open();
	logger_println("<- DataManager::newProbingPoint()");
}

void DataManager::terminate()
{
	logger_println("-> DataManager::terminate()");
	close();
	logger_println("<- DataManager::terminate()");
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


void DataManager::setFolder(const char * directory)
{
	logger_println("-> DataManager::setFolder()");
	memset(m_directory_name, '\0', sizeof m_directory_name);
	strcpy(m_directory_name, directory);

	logger_print("-- DataManager::m_directory: ");
	logger_println(m_directory_name);
	logger_println("<- DataManager::setFolder()");
}

void DataManager::setFile(const char * filename)
{
	logger_println("-> DataManager::setFile()");
	memset(m_file_name, '\0', sizeof m_file_name);
	strcpy(m_file_name, filename);

	logger_print("-- DataManager::m_file_name: ");
	logger_println(m_file_name);
	logger_println("<- DataManager::setFile()");
}

void DataManager::open()
{
	logger_println("-> DataManager::open()");
	char path[33] = { "\0" };
	sprintf(path, "%s/%s", m_directory_name, m_file_name);

	logger_print("-- DataManager::open: ");
	logger_println(path);

	File * file = new File();
	*file = SD.open(path, FILE_WRITE);
	m_file = file;
	logger_println("<- DataManager::open()");
}

void DataManager::close()
{
	logger_println("-> DataManager::close()");
	if (m_file != NULL)
	{
		logger_println("-- closing file");
		m_file->close();
		logger_println("-- deleting file instance");
		delete m_file;
	}
	logger_println("<- DataManager::close()");
}

// void DataManager::initLog()
// {
// 	if (m_file != NULL)
// 	{
// 		return;
// 	}


// 	char number[5];
// 	memset(number, '\0', 5);
// 	sprintf(number, "%d", m_file_number);


// 	char filename[11];
// 	memset(filename, '\0', 11);
// 	strcpy(filename, "Punto_");
// 	strcat(filename, number);

// 	m_file = SD.open(filename, FILE_WRITE);


// }