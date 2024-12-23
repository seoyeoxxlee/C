#include <stdio.h>
#include <wiringPi.h>
#define TRIG 1	// gpio 18
#define ECHO 4	// gpio 4

// Use BuzzerSong2.c unsigned int t, T => unsigned int start, end


int main (void) {
	if (wiringPiSetup() == -1) {
		return 1;
	}
	
	// pin = 1
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);
	
	unsigned int start, end;
	float distance;
	
	while(1) {
		digitalWrite(TRIG, 0);
		delayMicroseconds(2);	
		
		digitalWrite(TRIG, 1);
		delayMicroseconds(10);	// delay for 10uS pulse
		digitalWrite(TRIG, 0);
		
		// same as while(digitalRead(ECHO) == 0)
		while(!digitalRead(ECHO)); 
		start = micros();
			
		while(digitalRead(ECHO));
		end = micros();
		
		distance = (float)(end - start) / 58.0;
		
		printf("distace = %.1f\n", distance);
		delay(1000);
	}
}
	
/***
	// calculation
	while (1) {
		digitalWrite(TRIG, 0) 
		delayMicroseconds(2);	
		
		digitalWrite(TRIG, 1);
		delayMicroseconds(10);	// delay for 10uS pulse
		digitalWrite(TRIG, 0);
		
		// wait ECHO until 1  
		while(digitalRead(ECHO) == 0);
		long startTime = micros();
		
		// wait ECHO until 0
		while(digitalRead(ECHO) == 1);
		long endTime = micros();
		
		long duration = endTime - startTime;
		
		// distance
		double distance = duration/58.0;
		
		print(distance);
		delay(500);
	}
	return 0;
}
***/
		
		
		
		
		
		
		
