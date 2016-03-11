#ifndef ENCODER_H
#define ENCODER_H

#include <inttypes.h>

#define PIN_ENCODER_PHA 	31
#define PIN_ENCODER_PHB 	33
#define PIN_ENCODER_BUTTON 	35

#define MASK_ENCODER_PHA 	0x01
#define MASK_ENCODER_PHB 	0x02
#define MASK_ENCODER_BUTTON 0x04

#define ENCODER_POSITION_0 0
#define ENCODER_POSITION_1 2
#define ENCODER_POSITION_2 3
#define ENCODER_POSITION_3 1

class Encoder
{
	public:
		Encoder();
		~Encoder();

		void init();

		int16_t getMovement();
		bool getClick();
};

#endif // ENCODER_H