// 라즈베리파이와 MCP3004 아날로그-디지털 변환기 (ADC)를 사용하여 아날로그 데이터를 읽는 프로그램.
#include <stdio.h>
#include <wiringPi.h>
#include <mcp3004.h>    // MCP3004 ADC 모듈과 통신하기 위한 WiringPi 라이브러리의 헤더 파일

// MCP3004와 통신 시 사용할 기준값(BASE) 정의. ADC 채널 읽을 때 BASE를 기준으로 채널 번호지정
#define BASE 100    // ex: analogRead(BASE + 0)는 0번 채널을 읽음

// SPI 채널 번호 정의. MCP3004 SPI 인터페이스를 사용하므로 이를 통해 데이터를 읽음
#define SPI_CHAN 0  //  SPI 채널 0은 라즈베리파이에서 기본으로 설정된 SPI 채널.

int main(void) {                  
	
	// wiringPi setup
	if (wiringPiSetup() == -1) {
		return 1;
	}
    
    // MCP3004 초기화
    // MCP3004의 4개의 아날로그 입력 채널을 WiringPi에 연결
	mcp3004Setup(BASE, SPI_CHAN);
    
    // MCP3004에서 읽은 아날로그 값을 저장하기 위한 변수 선언
	int x;
	
    // 무한루프를 통해 아날로그 값을 계속 읽고 출력.
	while(1) {
		x = analogRead(BASE);   // 이 값은 0~1023 사이의 정수로 반환됨
		printf("%d\n", x);      // 0은 최소 아날로그 입력값(0V)을 나타냄
		delay(500);             // 1023은 최대 아날로그 입력값(3.3V or 5V)을 나타냄
	}
	
	return 0;
}
