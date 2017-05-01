// F_CPU tells util/delay.h our clock frequency
#define F_CPU 8000000UL	// Clock frequency (8MHz)
#define RENDER_TYPES 6

#ifndef ANIMATIONS_H_
#define ANIMATIONS_H_

#include <util/delay.h>

typedef void (*RenderFunc)(int8_t, int);

void drawRowGradient(int8_t row, int frame);
void drawRowMemDump(int8_t row, int frame);
void drawRowSpinner(int8_t row, int frame);
void drawRowPacman(int8_t row, int frame);
void drawPong(int8_t row, int frame);
void drawGameOfLife(int8_t row, int frame);

const RenderFunc renderFuncs[RENDER_TYPES] = {
	&drawRowGradient,
	&drawRowMemDump,
	&drawRowSpinner,
	&drawRowPacman,
	&drawPong,
	&drawGameOfLife
};

#endif /* ANIMATIONS_H_ */