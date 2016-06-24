#ifndef DATA_LOGGER_H
#define DATA_LOGGER_H

#include "SD.h"

#include <stdint.h>

class DataManager
{
	public:
		DataManager();
		~DataManager();

		void newBuild(const char * name);
		void newProbingPoint();
		void terminate();

		void resetPointNumber();
		void incrementPointNumber();
		uint16_t getPointNumber();

	private:
		void setFolder(const char * directory);
		void setFile(const char * filename);

		void open();
		void close();

	private:
		char * m_directory_name;
		char * m_file_name;
		uint16_t m_file_number;

		File * m_file;

		float m_distance;
		float m_pressure;
};

#endif // DATA_LOGGER_H