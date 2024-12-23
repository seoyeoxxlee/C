// LED의 밝기를 사용자로부터 입력받은 비율(0~100%)로 조정하는 프로그램
#include <pthread.h>    // thread를 사용하기 위한 라이브러리. 프로그램에서 여러 작업을 동시에 실행할 수 있도록 함
#include <stdio.h>
#include <wiringPi.h>

#define LED_PIN 1
#define INTERVAL 10 // LED의 깜빡이는 주기 설정 10ms 주기로 LED를 켜고 끈다

int dutycycle = 30; // LED의 초기 밝기를 30%로 설정
int running = 1;    // 프로그램의 실행 여부 1: 실행중

// LED를 제어하는 스레드 함수로 밝기(duty cycle)에 따라 LED를 켜고 끈다.
void *threadRoutine(void *arg){
	while (running){
		int onTime = (dutycycle *INTERVAL)/100; // LED가 켜져 있어야 할 시간을 계산 (초기 onTime = 3ms)
		int offTime = INTERVAL - onTime;    // LED가 꺼져 있어야 할 시간을 계산
			// LED ON
			digitalWrite(LED_PIN,HIGH);
			delay(onTime);  // onTime 동안 켜둠
			// LED OFF
			digitalWrite(LED_PIN,LOW);
			delay(offTime); // offTime 동안 꺼둠
		}
		return NULL;
	}

// 사용자의 입력을 처리하는 스레드함수로 사용자가 입력한 값(0~100%)을 받아 dutycycle을 업데이트
void *threadRoutine2(void *arg){ // user input handler function
	int input;  // 사용자로부터 입력받을 값 변수
	while(running){
		printf("led (0%~100%) : ");
		scanf("%d",&input); // 사용자가 입력한 숫자를 input 변수에 저장
		
		if (input >= 0 && input <=100) {    // 입력값이 0~100 사이인지 확인
			dutycycle = input;  // 입력값을 dutycycle에 저장하여 LED 밝기 변경
			printf("led : %d%%\n", dutycycle);
		}
		else {
			printf("error\n");
		}
	}
		return NULL;
	
}
	

int main(){
	
	// wiring pi setup
	if (wiringPiSetup() == -1){
	return 1;
	}
    
    // LED가 연결된 핀을 출력모드(OUTPUT)로 설정
	pinMode(LED_PIN,OUTPUT);
	
	// 두 개의 스레드를 생상하기 위한 변수 선언
	pthread_t threadID1,threadID2;
	
    // 첫 번째와 두 번째 스레드 생성하여 threadRoutine, threadRoutine2 실행
	pthread_create(&threadID1,NULL,threadRoutine,NULL);
	pthread_create(&threadID2,NULL,threadRoutine2,NULL);
    
    // 첫 번째 스레드가 끝날 때까지 기다림
	pthread_join(threadID1,NULL);
    // 두 번째 스레드가 끝날 때까지 기다림
	pthread_join(threadID2,NULL);
	
	// 프로그램 종료 전에 LED OFF
	digitalWrite(LED_PIN,LOW);
	printf("end\n");
	return 0;
}
