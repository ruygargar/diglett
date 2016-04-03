#ifndef SCREEN_TERMINATE_H
#define SCREEN_TERMINATE_H

#include "Screen.h"

#include "Text.h"

class ScreenTerminate : public Screen
{
	public:
		ScreenTerminate();
		~ScreenTerminate();

		void control();
		Event_t compute();
		void draw();

	private:
		Text * m_text;

};
#endif // SCREEN_TERMINATE_H