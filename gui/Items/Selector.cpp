#include "Selector.h"

#include "LiquidCrystal.h"
extern LiquidCrystal lcd;

Selector::Selector(uint8_t column, uint8_t items)
	: ScreenItem(0, column)
	, m_items(items)
	, m_selected_element(0)
	, m_selected_item(255)
{}

Selector::~Selector()
{}

void Selector::right()
{
	if (m_selected_element < (m_items - 1))
	{
		m_selected_element++;
	}
}

void Selector::left()
{
	if (m_selected_element > 0)
	{
		m_selected_element--;
	}
}

void Selector::push()
{
	m_selected_item = m_selected_element;
}

uint8_t Selector::item()
{
	uint8_t tmp_item = m_selected_item;
	m_selected_item = 255;
	return tmp_item;
}

void Selector::draw()
{
	for (uint8_t i = 0; i < m_items; i++)
	{
		lcd.setCursor(m_column, i);
		if (i == m_selected_element)
		{
			lcd.write('>');
		}
		else
		{
			lcd.write(' ');
		}
	}
}

