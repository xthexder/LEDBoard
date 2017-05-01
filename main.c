#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "animations.h"

char triangle(char x) {
	char y = x & 0xF;
	if (y >= 8) {
		return 0xF - y;
	} else return y;
}

int main() {
	CLKPSR = 0; // Clock scaler = 1 (Full 8MHz)
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	
	unsigned char *persist = (unsigned char*) 0x98;
	persist[0]++;
	persist[1]++;
	if (persist[0] >= RENDER_TYPES) persist[0] = 0;
	
	TCCR1B = 1 << CS12; // Set timer1 to 8MHz/256
	TCCR1B |= 1 << WGM12; // Compare against OCR1A
	TIMSK = 1 << OCIE1A; // Enable timer1 compare A interrupt
	OCR1A = (persist[0] < 4 ? 5 : 10) * 1000000 / 256; // Max timer value = 10 seconds
	sei(); // Enable global interrupts
	
	DDRA = 0xFF; // setup output pins
	DDRB = 0x0F;

	PORTB = 0x00; // Reset shift register
	PORTA = 0x00; // Turn off all LEDs
	PORTB = 0x04; // Enable shift register
	int8_t row = 0;
	int frame = 0;
	char lookup[8];
	
	RenderFunc drawRow = renderFuncs[persist[0]];
	while (1) {
		PORTA = 0;
		if (row == 0) PORTB |= 1; // Shift input up
		PORTB |= 2; // Clock up
		if (row == 0) PORTB &= ~(1); // Shift input down
		PORTB &= ~(2); // Clock down
		
		PORTA = lookup[row];
		(*drawRow)(row, frame);
		lookup[row] = PORTA;

		row++;
		if (row >= 8) {
			frame++;
			row = 0;
		}
	}
	return 0;
}

// Timer1 compare A (go to sleep)
ISR(TIM1_COMPA_vect) {
	DDRA = 0; // Set output pins to Hi-Z
	DDRB = 0;
	sleep_mode(); // Go to sleep
}