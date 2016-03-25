#ifndef SCREEN_ITEM_H
#define SCREEN_ITEM_H

#include <inttypes.h>

class ScreenItem
{
	public:
		ScreenItem(uint8_t row, uint8_t column);
		~ScreenItem();

		virtual void draw() = 0;

	protected:
		uint8_t m_row;
		uint8_t m_column;
};

#endif // SCREEN_ITEM_H