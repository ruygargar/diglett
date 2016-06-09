#ifndef SCREEN_PROBING_H
#define SCREEN_PROBING_H

#include "Observer.h"
#include "SensorManager.h"
#include "Screen.h"

#include "Text.h"
#include "Textbox.h"
#include "Button.h"

class ScreenProbing : public Screen, public Observer<sensor_t>
{
	public:
		ScreenProbing(Subject<sensor_t> * model);
		~ScreenProbing();

		void control();
		Event_t compute();
		void draw();

		void update(sensor_t value);

	private:
		Text * m_text_distance;
		Textbox * m_text_distance_value;
		Text * m_text_pressure;
		Textbox * m_text_pressure_value;
		Text * m_text_menu;
		Button * m_button;
};

#endif // SCREEN_PROBING_H