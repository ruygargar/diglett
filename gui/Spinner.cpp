#include "Spinner.h"

#include "Logger.h"

#include "LiquidCrystal.h"
extern LiquidCrystal lcd;

Spinner::Spinner(uint8_t row, SpinnerType_t type)
	: ScreenItem(row, 0) 
	, m_selected_element(0)
	, m_selected_character(0x00)
{
	logger_println("-> Spinner()");
	switch(type)
	{
		case SPINNERTYPE_NUMERIC:
		{
			m_items = spinner_numeric_items;
			m_lut = &spinner_numeric_lut[0];
			break;
		}

		case SPINNERTYPE_ALPHANUMERIC:
		{
			m_items = spinner_alphanumeric_items;
			m_lut = &spinner_alphanumeric_lut[0];
			break;
		}
	}
	logger_println("<- Spinner()");
}

Spinner::~Spinner()
{
	logger_println("-> ~Spinner()");
	logger_println("<- ~Spinner()");
}

void Spinner::right()
{
	logger_println("-> Spinner::right()");

	if (m_selected_element < (m_items - 1))
	{
		m_selected_element++;
	}

	logger_println("<- Spinner::right()");
}

void Spinner::left()
{
	logger_println("-> Spinner::left()");

	if (m_selected_element > 0)
	{
		m_selected_element--;
	}

	logger_println("<- Spinner::left()");
}

void Spinner::push()
{
	logger_println("-> Spinner::push()");

	m_selected_character = (m_lut[m_selected_element]);

	logger_println("<- Spinner::push()");
}

char Spinner::character()
{
	logger_println("-> Spinner::character()");

	char tmp_char = m_selected_character;
	m_selected_character = 0x00;

	logger_println("<- Spinner::character()");
	return tmp_char;
}

void Spinner::draw()
{
	logger_println("-> Spinner::draw()");

	lcd.setCursor(0, m_row);
	logger_print("lcd.setCursor(0, ");
	logger_print(m_row);
	logger_println(");");

	int16_t aux = 0; 
	for (uint8_t i = 0; i < 7; i++)
	{
		aux = (m_selected_element - 7) + i;
		if (aux < 0)
		{
			lcd.write(' ');
		}
		else
		{
			lcd.write(*(m_lut + aux));
		}
	}

	lcd.write(' ');
	lcd.write('<');
	lcd.write(*(m_lut + m_selected_element));
	lcd.write('>');
	lcd.write(' ');

	for (uint8_t i = 12; i < 20; i++)
	{
		aux = (m_selected_element - 11) + i;
		if (aux > (m_items - 1))
		{
			lcd.write(' ');
		}
		else
		{
			lcd.write(*(m_lut + aux));
		}
	}

	logger_println("<- Spinner::draw()");
}