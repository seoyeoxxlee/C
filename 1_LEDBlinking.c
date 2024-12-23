#include <stdio.h>
#include <wiringPi.h>
#define PIN_NUM 7

int main (void) {

	// wiringPi setup
	if (wiringPiSetup() == -1) {
		return -1;
	}

	// pin = 7
	pinMode(PIN_NUM, OUTPUT);

	// LED toggle
	while(1) {
		digitalWrite(PIN_NUM, 1);
		delay(500);
		digitalWrite(PIN_NUM, 0);
		delay(500);
	}

	return 0;
	
}
