#ifndef SCREEN_MENU_H
#define SCREEN_MENU_H

#include "Screen.h"

#include "Text.h"
#include "Selector.h"

class ScreenMenu : public Screen
{
	public:
		ScreenMenu();
		~ScreenMenu();

		void control();
		Event_t compute();
		void draw();

	private:
		Text * m_text_item_0;
		Text * m_text_item_1;
		Text * m_text_item_2;
		Text * m_text_item_3;

		Selector * m_selector;	
};

#endif SCREEN_MENU_H