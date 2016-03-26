#ifndef TEXT_H
#define TEXT_H

#include "ScreenItem.h"

class Text : public ScreenItem
{
	public:
		Text(uint8_t row, uint8_t column, char * string);
		~Text();

		void draw();

	private:
		char * m_text;
		uint8_t m_length;
};

#endif // TEXT_H