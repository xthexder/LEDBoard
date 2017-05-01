#include <avr/io.h>

void drawRowSpinner(int8_t row, int frame) {
	char angle = (frame >> 1) & 31;
	int8_t y = row - 4;
	int8_t slope = angle & 7;
	int8_t slope2;
	if (angle & 8) {
		slope2 = 64 / (8 - slope);
		slope -= 8;
	} else {
		slope2 = -64 / slope;
	}
	int8_t min = ((y * slope2) >> 3) + 4;
	if (!(angle & 15)) {
		min = row < 4 ? 8 : -1;
	}
	int8_t max = ((y * slope) >> 3) + 4;
	char val = 0;
	for (int8_t x = 0; x < 8; x++) {
		if (x >= min && x <= max) val |= 1 << x;
		if (x <= min && x >= max) val |= 1 << x;
	}
	PORTA = angle < 16 ? val : ~val;
}
