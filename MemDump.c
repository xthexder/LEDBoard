#include <avr/io.h>

char dataMem[8];

void drawRowMemDump(int8_t row, int frame) {
	if ((frame & 0x7F) == 0) {
		if (row == 7) {
			int8_t *mem = (int8_t*) (0x4000 + ((frame >> 7) % 0xFF));
			dataMem[row] = *mem;
		} else {
			dataMem[row] = dataMem[row + 1];
		}
	}
	PORTA = dataMem[row];
}
