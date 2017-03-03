#include "fire.h"

void FireSensInit(void) {
	FIRE_SENS_DDR &= ~_BV(FIRE_SENS_PIN);
	FIRE_SENS_PORT |= _BV(FIRE_SENS_PIN);
}