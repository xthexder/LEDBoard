#include <avr/io.h>
#include "util.h"

const char dataWave[15] = {
	//0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1, 0
	0, 0, 0, 0, 1, 3, 5, 7, 5, 3, 1, 0, 0, 0, 0
};

void drawRowGradient(int8_t row, int frame) {
	char val = 0xFF;
	char height = triangle(row + frame / 2);
	for (int8_t i = 0; i < 8; i++) {
		PORTA = val;
		for (int8_t j = 0; j < 8; j++) {
			if (dataWave[height + j] <= i) val &= ~(1 << j);
		}
	}
	PORTA = val;
}