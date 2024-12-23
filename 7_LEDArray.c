// LED 4개 순서대로 깜빡이기
#include <stdio.h>
#include <wiringPi.h>

#define LEDS_NUM 4 // LED 4개 사용할거임

int main(void) {
	if (wiringPiSetup() == -1) {
		return 1;
	}

	// LED ARRAY
    // 포트 배열에 LED 4개의 핀 번호(2, 3, 4, 5) 저장
	int port[LEDS_NUM] = {2, 3, 4, 5};
    
    // for loop으로 4개의 핀을 출력모드(OUTPUT)로 설정
	for (int i=0; i<LEDS_NUM; i++) {
	pinMode(port[i], OUTPUT);
	}

    // 현재 LED의 번호를 나타낼 변수
    // 처음에는 0으로 시작해 2번핀(첫 번째 LED)을 의미
	int cur=0;

	while(1) {
		digitalWrite(port[cur], HIGH); // LED ON
		delay(1500);    // 1.5초 유지
		digitalWrite(port[cur], LOW);   // LED OFF
        
        // 현재 LED 번호를 하나씩 증가시키고, cur이 LED 개수인 4를 넘어가게 되면
        // 다시 0으로 돌아가게 됨(%LEDS_NUM)
		cur = (cur+1)%LEDS_NUM;
	}

	return 0;
}
