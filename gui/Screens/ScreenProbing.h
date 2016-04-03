#ifndef SCREEN_PROBING_H
#define SCREEN_PROBING_H

#include "Screen.h"

#include "Text.h"
#include "Button.h"

class ScreenProbing : public Screen
{
	public:
		ScreenProbing();
		~ScreenProbing();

		void control();
		Event_t compute();
		void draw();

	private:
		Text * m_text_distance;
		Text * m_text_distance_value;
		Text * m_text_pressure;
		Text * m_text_pressure_value;
		Text * m_text_menu;
		Button * m_button;
};

#endif // SCREEN_PROBING_H