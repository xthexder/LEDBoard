#include <avr/io.h>
#include <string.h>

char lifeData[8];/* = {
	0b01000000,
	0b00100000,
	0b11100000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000
};*/
char lifeData2[8];

void drawGameOfLife(int8_t row, int frame) {
	if (frame == 0) {
		unsigned char *persist = (unsigned char*) 0x98;
		memcpy(&lifeData, (char*) 0x4000 + persist[1], 8);
	}

	if ((frame & 0x7F) == 0) {
		if (row == 0) memcpy(&lifeData2, &lifeData, 8);
		for (int8_t x = 0; x < 8; x++) {
			char count = 0;
			for (int8_t r = row-1; r <= row+1; r++) {
				if ((lifeData[r&7] & (1 << ((x-1)&7))) != 0) count++;
				if (r != row && (lifeData[r&7] & (1 << x)) != 0) count++;
				if ((lifeData[r&7] & (1 << ((x+1)&7))) != 0) count++;
			}
			
			if (count == 3) {
				lifeData2[row] |= 1 << x;
			} else if (count != 2) {
				lifeData2[row] &= ~(1 << x);
			}
		}
		if (row == 7) memcpy(&lifeData, &lifeData2, 8);
	}
	PORTA = lifeData[row];
}