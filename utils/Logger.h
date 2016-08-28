#ifndef LOGGER_H
#define LOGGER_H

#define LOGGER_BAUDRATE 115200
#define LOGGER_LEDPIN   13

void logger_init();

void logger_print(char * string);
void logger_print(const char * string);
void logger_print(int number);
void logger_print(float number);

void logger_println(char * string);
void logger_println(const char * string);
void logger_println(int number);
void logger_println(float number);

void logger_signal_on();
void logger_signal_off();

#endif // LOGGER_H