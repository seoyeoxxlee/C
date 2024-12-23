#include <stdio.h>
#include <wiringPi.h>
#define PIN_NUM 1 // gpio 1

// ABC song ..
// do do sol sol la la sol ~
// dif version => change delayMicroseconds -> T = micros(); while(micros() < T = 3000000);


int main (void) {
	if (wiringPiSetup() == -1) {
		return 1;
	}
	
	// buzzer pin = 1
	pinMode(PIN_NUM, OUTPUT);

	unsigned int t, T;
	T = micros(); // current time

	// buzzer control
	while(micros() < T+3000000) {
		
		// first do
		for (int i=0; i<200; i++) {
			digitalWrite(PIN_NUM, 1);
			delayMicroseconds(1911);
			digitalWrite(PIN_NUM, 0);
			delayMicroseconds(1911);
		}
		
		
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
