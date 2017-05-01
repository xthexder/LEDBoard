#include <avr/io.h>
#include <stdlib.h>
#include "util.h"

const char dataPacman[8] = {
	0b00111100,
	0b01111110,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b01111110,
	0b00111100
};

void drawRowPacman(int8_t row, int frame) {
	char angle = triangle(frame >> 2);
	int8_t y = abs(row - 4);
	int8_t edge = y * 8 / (angle - 8);
	char val = 0;
	for (int8_t x = 0; x < 8; x++) {
		if (x - 4 >= edge) val |= 1 << x;
	}
	PORTA = val & dataPacman[row];
}
