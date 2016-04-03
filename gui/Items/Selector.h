#ifndef SELECTOR_H
#define SELECTOR_H

#include <inttypes.h>

#include "Controller.h"
#include "ScreenItem.h"

class Selector : public Controller, public ScreenItem
{
	public:
		Selector(uint8_t column, uint8_t items);
		~Selector();

		uint8_t item();

		void draw();

	private:
		void right();
		void left();
		void push();

	private:
		uint8_t m_items;
		uint8_t m_selected_element;
		uint8_t m_selected_item;
};

#endif // SELECTOR_H