#include <stdio.h>
#include <wiringPi.h>

#define PIN_NUM 1

int main (void) {
	// wiringPi setup
	if (wiringPiSetup() == -1) {
		return -1;
	}

	// pin =
	pinMode(PIN_NUM, INPUT);

	// switch toggle
	int x;

	while(1) {
		x=digitalRead(PIN_NUM);
		printf("%d\n", x);
		
	}

}
