#ifndef POINT_SCREEN_H
#define POINT_SCREEN_H

#include "Screen.h"

#include "Button.h"
#include "Text.h"

class ScreenPoint : public Screen
{
	public:
		ScreenPoint();
		~ScreenPoint();

		void control();
		Event_t compute();
		void draw();

	private:
		Text * m_text_point;
		Text * m_text_instructions;
		Button * m_button;
};

#endif // POINT_SCREEN_H