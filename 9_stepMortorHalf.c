// Step Mortor 제어하는 프로그램 (Half Step)
#include <stdio.h>
#include <wiringPi.h>

// 스텝모터를 제어하기 위해 사용되는 GPIO 핀 번호 정의
// 각각 스텝모터의 입력 핀에 연결된 GPIO 핀 번호다.
#define IN1 0 	// GPIO 1
#define IN2 1	// GPIO 2
#define IN3 2	// GPIO 3
#define IN4 3	// GPIO 4

int main() {
	// wiringPi setup
	if (wiringPiSetup() == -1) {
		return -1;
	}
    
    // 스텝모터의 입력핀이 연결된 GPIO 핀을 출력모드(OUTPUT)으로 설정
    // 핀모드를 설정해야 HIGH/LOW 신호를 보낼 수 있음
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	pinMode(IN3, OUTPUT);
	pinMode(IN4, OUTPUT);
	
	// Half Step 신호 정의
	int halfStep[8][4] = {
		{1, 0, 0, 0},   // IN1을 켜고 나머지는 끔
		{1, 1, 0, 0},   // IN1과 IN2만 켜고 나머지는 끔
		{0, 1, 0, 0},   // IN2를 켜고 나머지는 끔
		{0, 1, 1, 0},   // IN2과 IN3만 켜고 나머지는 끔
		{0, 0, 1, 0},   // IN3을 켜고 나머지는 끔
		{0, 0, 1, 1},   // IN3과 IN4만 켜고 나머지는 끔
		{0, 0, 0, 1},   // IN4를 켜고 나머지는 끔
		{1, 0, 0, 1}    // IN4과 IN1만 켜고 나머지는 끔
	};
	
	while(1) {
        // HalfStep의 배열을 순서대로 읽고 각 핀에 신호를 보내서 스텝모터가 회전
		for (int i=0; i<8; i++) {
			digitalWrite(IN1, halfStep[i][0]);
			digitalWrite(IN2, halfStep[i][1]);
			digitalWrite(IN3, halfStep[i][2]);
			digitalWrite(IN4, halfStep[i][3]);
			
			delay(5);   // 다음 스텝으로 넘어가기 전 5ms 동안 멈춤. 이 시간을 조정하면 모터 회전 속도가 달라짐
		}
	}
	return 0; 
}









