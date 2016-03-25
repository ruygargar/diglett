#include "ScreenItem.h"

#include "Logger.h"

ScreenItem::ScreenItem(uint8_t row, uint8_t column)
	: m_row(row)
	, m_column(column)
{
	logger_println("-> ScreenItem()");
	logger_println("<- ScreenItem()");
}

ScreenItem::~ScreenItem()
{
	logger_println("-> ~ScreenItem()");
	logger_println("<- ~ScreenItem()");
}