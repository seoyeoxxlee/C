#include <stdio.h>
#include <wiringPi.h>
#define PIN_NUM 1 // gpio 1

// ABC song ..
// do do sol sol la la sol ~



int main (void) {
	if (wiringPiSetup() == -1) {
		return 1;
	}
	
	// buzzer pin = 1
	pinMode(PIN_NUM, OUTPUT);


	// buzzer control
	while(1) {
		// first do
		for (int i=0; i<200; i++) {
			digitalWrite(PIN_NUM, 1);
			delayMicroseconds(1911);
			digitalWrite(PIN_NUM, 0);
			delayMicroseconds(1911);
		}
		
		delay(500);
		
		// second do
		for (int i=0; i<200; i++) {
			digitalWrite(PIN_NUM, 1);
			delayMicroseconds(1911);
			digitalWrite(PIN_NUM, 0);
			delayMicroseconds(1911);
		}
		
		delay(250);
		
		// first sol
		for (int i=0; i<200; i++) {
			digitalWrite(PIN_NUM, 1);
			delayMicroseconds(1275);
			digitalWrite(PIN_NUM, 0);
			delayMicroseconds(1275);
		}
		
		delay(250);
		
		// second sol
		for (int i=0; i<200; i++) {
			digitalWrite(PIN_NUM, 1);
			delayMicroseconds(1275);
			digitalWrite(PIN_NUM, 0);
			delayMicroseconds(1275);
		}
		
		delay(250);
		
		// first la
		for (int i=0; i<200; i++) {
			digitalWrite(PIN_NUM, 1);
			delayMicroseconds(1136);
			digitalWrite(PIN_NUM, 0);
			delayMicroseconds(1136);
		}
		
		delay(250);
		
		// second la
		for (int i=0; i<200; i++) {
			digitalWrite(PIN_NUM, 1);
			delayMicroseconds(1136);
			digitalWrite(PIN_NUM, 0);
			delayMicroseconds(1136);
		}
		
		delay(250);
		
		// third sol
		for (int i=0; i<200; i++) {
			digitalWrite(PIN_NUM, 1);
			delayMicroseconds(1275);
			digitalWrite(PIN_NUM, 0);
			delayMicroseconds(1275);
		}
		
		delay(250);
		
	}

	return 0;
}
