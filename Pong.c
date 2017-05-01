#include <avr/io.h>
#include <stdlib.h>

char playerOne = 128;
char playerTwo = 128;

char ballX = 64;
char ballY = 128;
int8_t speedX = 3;
int8_t speedY = 2;

const int8_t paddleSpeed = 3;

void drawPong(int8_t row, int frame) {
	if (row == 0 && (frame & 0x3) == 0) {
		ballX += speedX;
		ballY += speedY;
		if (ballX >= (255 - 32) || ballX < 32) speedX *= -1;
		if (ballY >= (255 - 16) || ballY < 16) speedY *= -1;
		if (speedX > 0) {
			if (ballY > playerOne) {
				playerOne += paddleSpeed;
			} else playerOne -= paddleSpeed;
		} else {
			if (ballY > playerTwo) {
				playerTwo += paddleSpeed;
			} else playerTwo -= paddleSpeed;
		}
	}
	
	char out = 0;
	if (abs(playerOne - 15 - (row << 5)) < 48) out |= 0b10000000;
	if (abs(playerTwo - 15 - (row << 5)) < 48) out |= 0b00000001;
	
	int offsetY = abs(ballY - 16 - (row << 5));
	if (offsetY < 0) offsetY = -offsetY;
	if ((frame & 15) << 5 > offsetY * 20) {
		out |= 1 << (ballX >> 5);
	}
	
	PORTA = out;
}
