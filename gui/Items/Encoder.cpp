#include "Arduino.h"
#include "Encoder.h"

static uint8_t timer_software = 0;

static int16_t encoder_position;
static uint8_t encoder_input_last;

static bool button_clicked;
static uint8_t button_input_last;

static uint8_t read_pins();
static void update_encoder();
static void update_button();

Encoder::Encoder()
{
	// Init pins
	pinMode(PIN_ENCODER_PHA, INPUT);
	digitalWrite(PIN_ENCODER_PHA, HIGH);

	pinMode(PIN_ENCODER_PHB, INPUT);
	digitalWrite(PIN_ENCODER_PHB, HIGH);

	pinMode(PIN_ENCODER_BUTTON, INPUT);
	digitalWrite(PIN_ENCODER_BUTTON, HIGH);

	// Init Timer 5 and set the OVF interrupt (triggered every 125 us)
	TCCR5A = 0x03;
	TCCR5B = 0x19;

	OCR5AH = 0x1F;
	OCR5AL = 0x40;

	init();
}

Encoder::~Encoder()
{
	TIMSK5 &= ~(0x01);

	TCCR0A = 0x00;
	TCCR5B = 0x00;

	OCR5AH = 0x00;
	OCR5AL = 0x00;
}

void Encoder::init()
{
	TIMSK5 &= ~(0x01);

	encoder_input_last = read_pins();
	encoder_position = 0;

	button_input_last = read_pins();
	button_clicked = false;

	TCNT5H = 0x00;
	TCNT5L = 0x00;

	TIMSK5 |= 0x01;
}

int16_t Encoder::getMovement()
{
	int16_t movement = encoder_position;
	encoder_position = 0;
	return movement;
}


bool Encoder::getClick()
{
	bool click = button_clicked;
	button_clicked = false;
	return click;
}

static uint8_t read_pins()
{
	uint8_t pins_vector = 0;

	if ( digitalRead(PIN_ENCODER_PHA) == 0 )
	{
		pins_vector |= MASK_ENCODER_PHA;
	}

	if ( digitalRead(PIN_ENCODER_PHB) == 0 )
	{
		pins_vector |= MASK_ENCODER_PHB;
	}

	if ( digitalRead(PIN_ENCODER_BUTTON)  == 0 )
	{
		pins_vector |= MASK_ENCODER_BUTTON;
	}

	return pins_vector;
}

static void update_encoder()
{
	// Read the input hardware
	uint8_t encoder_input = read_pins();

    // Process rotatory encoder events
    if (encoder_input != encoder_input_last)
	{
		switch (encoder_input & (MASK_ENCODER_PHA | MASK_ENCODER_PHB)) {
		case ENCODER_POSITION_0:
			if ( (encoder_input_last & (MASK_ENCODER_PHA | MASK_ENCODER_PHB)) == ENCODER_POSITION_3 )
			{
			    encoder_position++;
			}
			else if ( (encoder_input_last & (MASK_ENCODER_PHA | MASK_ENCODER_PHB)) == ENCODER_POSITION_1 )
			{
			    encoder_position--;
			}
			break;

		case ENCODER_POSITION_1:
		    if ( (encoder_input_last & (MASK_ENCODER_PHA | MASK_ENCODER_PHB)) == ENCODER_POSITION_0 )
		    {
		        encoder_position++;
		    }
		    else if ( (encoder_input_last & (MASK_ENCODER_PHA | MASK_ENCODER_PHB)) == ENCODER_POSITION_2 )
		    {
		        encoder_position--;
		    }
		    break;

		case ENCODER_POSITION_2:
		    if ( (encoder_input_last & (MASK_ENCODER_PHA | MASK_ENCODER_PHB)) == ENCODER_POSITION_1 )
		    {
		        encoder_position++;
		    }
		    else if ( (encoder_input_last & (MASK_ENCODER_PHA | MASK_ENCODER_PHB)) == ENCODER_POSITION_3 )
		    {
		        encoder_position--;
		    }
		    break;

		case ENCODER_POSITION_3:
		    if ( (encoder_input_last & (MASK_ENCODER_PHA | MASK_ENCODER_PHB)) == ENCODER_POSITION_2 )
		    {
		        encoder_position++;
		    }
		    else if ( (encoder_input_last & (MASK_ENCODER_PHA | MASK_ENCODER_PHB)) == ENCODER_POSITION_0 )
		    {
		        encoder_position--;
		    }
		    break;
		}
	}

	// Update the phases
	encoder_input_last = encoder_input;
}

static void update_button()
{
	// Read the hardware
	uint8_t button_input = read_pins();

	// Process button click event
	bool clicked = ((button_input & MASK_ENCODER_BUTTON) && (~(button_input_last) & MASK_ENCODER_BUTTON));

	// Short-press management
	if (clicked == true)
	{
		button_clicked = true;
	}

	button_input_last = button_input;
}

ISR(TIMER5_OVF_vect)
{
	// Every 500 us
	timer_software++;
	update_encoder();

	// Every 10 ms
	if (timer_software % 20 == 0)
	{
		update_button();
		timer_software = 0;
	}
}

