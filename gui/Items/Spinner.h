#ifndef SPINNER_H
#define SPINNER_H

#include <inttypes.h>

#include "Controller.h"
#include "ScreenItem.h"


typedef enum
{
	SPINNERTYPE_NUMERIC,
	SPINNERTYPE_ALPHANUMERIC
} SpinnerType_t;

static const uint8_t spinner_numeric_items = 12;
static char spinner_numeric_lut[spinner_numeric_items] =
{
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	0x07F, 0x7E 
};

static const uint8_t spinner_alphanumeric_items = 67;
static char spinner_alphanumeric_lut[spinner_alphanumeric_items] =
{
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
	'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
	'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
	'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
	'y', 'z', ' ', '-', '_', '0', '1', '2', '3', '4',
	'5', '6', '7', '8', '9', 0x07F, 0x7E
};

class Spinner : public Controller, public ScreenItem
{
	public:
		Spinner(uint8_t row, SpinnerType_t type);
		~Spinner();

		char character();

		void draw();

	private:
		void right();
		void left();
		void push();

	private:
		uint8_t m_items;
		char * m_lut;

		uint8_t m_selected_element;
		char m_selected_character;
};
#endif // SPINNER_H