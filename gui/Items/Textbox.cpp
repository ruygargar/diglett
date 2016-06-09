#include "Textbox.h"

#include "LiquidCrystal.h"
extern LiquidCrystal lcd;

Textbox::Textbox(uint8_t row)
	: ScreenItem(row, 0)
	, m_text(NULL)
	, m_length(21)
	, m_index(0)
{
	m_text = new char[m_length];
	memset(m_text, '\0', m_length);
}

Textbox::Textbox(uint8_t row, uint8_t column, uint8_t length)
	: ScreenItem(row, column)
	, m_text(NULL)
	, m_length(length)
	, m_index(0)
{
	m_text = new char[m_length];
	memset(m_text, '\0', m_length);
}

Textbox::~Textbox()
{
	delete m_text;
}

void Textbox::draw()
{
	lcd.setCursor(m_column, m_row);
	lcd.print(m_text);
}

void Textbox::pushChar(char character)
{
	if (m_index < m_length)
	{
		char * fill = m_text + m_index;
		*(fill) = character;
		fill++;
		*(fill) = '\0'; 
		m_index++;
	}
}

void Textbox::pushString(char * text)
{
	strncpy((m_text + m_index), text, (m_length - m_index));
	m_index = strlen(m_text);
}

void Textbox::popChar()
{
	if (m_index > 0)
	{
		char * fill = m_text + m_index - 1;
		*(fill) = '\0';
		m_index--;
	}
}

void Textbox::flush()
{
	m_index = 0;
	memset(m_text, '\0', m_length);
}

const char * Textbox::text()
{
	return m_text;
}