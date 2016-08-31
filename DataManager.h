#ifndef DATA_LOGGER_H
#define DATA_LOGGER_H

#include "Observer.h"
#include "SensorManager.h"
#include "SD.h"

#include <stdint.h>

class DataManager : public Observer<sensor_t>
{
	public:
		DataManager(Subject<sensor_t> * model);
		~DataManager();

		void newBuild(const char * name);
		void newProbingPoint();
		void terminate();

		void resetPointNumber();
		void incrementPointNumber();
		uint16_t getPointNumber();

		void update(sensor_t value);

	private:
		void setFolder(const char * directory);
		void setFile(const char * filename);

		void open();
		void close();

		bool filterData(float value);

	private:
		char * m_directory_name;
		char * m_file_name;
		uint16_t m_file_number;

		File * m_file;

		float m_data;
};

#endif // DATA_LOGGER_H