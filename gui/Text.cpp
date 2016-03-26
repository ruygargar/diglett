#include "Text.h"

#include "Logger.h"

#include "LiquidCrystal.h"
extern LiquidCrystal lcd;

Text::Text(uint8_t row, uint8_t column, char * string)
	: ScreenItem(row, column)
{
	m_length = strlen(string) + 1;
	m_text = new char[m_length];

	char * read_ptr = string;
	char * write_ptr = m_text;
	for (uint8_t i = 0; i < m_length; i++)
	{
		*(write_ptr) = *(read_ptr);
		read_ptr++;
		write_ptr++;
	}
	*(write_ptr) = '\0';
}

Text::~Text()
{
	delete m_text;
}

void Text::draw()
{
	lcd.setCursor(m_column, m_row);
	lcd.print(m_text);
}