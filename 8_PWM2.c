// Servo Mortor 제어 프로그램
// 사용자로부터 각도를 입력받아 Servo Mortor의 각도 조절
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h> // 소프트웨어 방식으로 PWM(펄스 폭 변조) 신호를 만들어주는 라이브러리로, 서보모터 제어에 필수

#define SERVO_PIN 1 // 서보모터가 연결된 핀 번호를 1로 설정

// calculating inserted angle to pwm
// 사용자가 입력한 각도(0-180도)를 PWM 신호 값으로 변환하는 함수
// 서보모터는 4-24의 PWM 값으로 0도 -> 4, 180도 -> 24
int angleToPwm(int angle) {
	int pwmValue = 4 + (angle * 20 / 180);
	return pwmValue;    // 계산된 PWM 값을 반환하여 서보모터에서 사용
}

// 서보모터를 제어하는 함수
void controlServo() {
	int angle;
	while(1) {
		printf("Enter angle (0-180): \n");
		if (scanf("%d", &angle) == 1) {   // 사용자가 입력한 숫자를 angle 변수에 저장. 숫자인지 확인, 성공시 1을 반환
			if (angle >= 0 && angle <= 180) {   // 각도가 0-180 사이인지 확인
				int pwmValue = angleToPwm(angle);   // 사용자가 입력한 각도를 PWM 값으로 변환
				softPwmWrite(SERVO_PIN, pwmValue);  // 변환된 PWM 값을 서보모터에 전달!! -> 서보모터가 해당각도로 움직임
				printf("servo: %d \n", angle);  // 현재 서보모터가 움직인 각도를 화면에 출력
			} else {
				printf("Enter number between 0-180. \n");
			}
		} else {
			printf("error \n");
		}
	}
}
	
// 프로그램 시작
int main(){
	
	// wiring pi setup
	if (wiringPiSetup() == -1){
	return 1;
	}
	
    // softPwmCreate() 함수로 서보모테를 제어할 PWM 신호 준비
    // 200은 PWM 값의 최대 범위, 준비에 실패하면 프로그램 종료
	if (softPwmCreate(SERVO_PIN, 0 , 200) != 0) {
		printf("Initialize sort PWM. \n");
		return 1;
	}
	
    // 위에서 만든 controlServo() 함수를 실행하여 서보모터 제어 시작
	controlServo();
    
	return 0;
}












