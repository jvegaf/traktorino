
#ifndef ARDUINO_POTKIT_H
#define ARDUINO_POTKIT_H
#include <Arduino.h>
#include <Multiplexer4067.h>
#include "pin_map.h"
#include "pots_map.h"

class PotKit  
{
	private:

	public:

		void begin();
		void read(void (*scc_func)(byte, byte, byte));

};
#endif
