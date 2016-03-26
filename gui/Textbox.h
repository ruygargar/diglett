#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <inttypes.h>

#include "ScreenItem.h"

class Textbox : public ScreenItem
{
	public:
		Textbox(uint8_t row);
		Textbox(uint8_t row, uint8_t column, uint8_t length);
		~Textbox();
	
		void draw();

		void pushChar(char character);
		void pushString(char * string);
		void popChar();

		const char * text();

	public: 
		char * m_text;
		uint8_t m_length;

		uint8_t m_index;
};

#endif // TEXTBOX_H