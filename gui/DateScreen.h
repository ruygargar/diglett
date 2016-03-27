#ifndef DATE_SCREEN_H
#define DATE_SCREEN_H

#include "Screen.h"

#include "Text.h"
#include "Textbox.h"
#include "Spinner.h"

class DateScreen : public Screen
{
	public:
		DateScreen();
		~DateScreen();

		void control();
		Event_t compute();
		void draw();

	private:
		Text * m_text;
		Textbox * m_textbox;
		Spinner * m_spinner;
};

#endif // DATE_SCREEN_H