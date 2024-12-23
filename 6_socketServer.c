#include <stdio.h> // 화면에 출력하거나 사용자 입력 받음
#include <string.h> // 데이터를 초기화 하고 문자열 다룸
#include <unistd.h> // 파일을 닫거나 다른 기본 작업
#include <sys/types.h> // 네트워크 통해 서버와 통신
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 3333   // 클라이언트와 서버가 서로 통신하기로 약속한 "문"의 번호

// LED 제어 정보를 담은 구조체
typedef struct {
	unsigned short LED_NUM; // 0~3 중에 어떤 LED를 제어할 지
	unsigned short MODE;    // LED를 켜거나(1) 끌지(0) 설정
} LED_control_t;    // 클라이언트가 보낸 데이터를 저장할 구조체


int main(void) {
	if(wiringPiSetup()==-1) {
		printf("WiringPi error\n");
		return 1;
	}
	
    // LED 핀 설정
	int LED_pins[4] = {0,1,2,3};    // LED를 제어할 핀 번호를 배열에 저장
    int led_states[4] = {0}; // 각 LED의 현재 상태를 저장 (0: OFF, 1: ON)
    
    // for loop을 통해 4개의 핀을 모두 출력(OUTPUT)모드로 설정하고, 꺼둔다(LOW)
	for(int i=0; i<4; i++) {
		pinMode(LED_pins[i], OUTPUT);
		digitalWrite(LED_pins[i], LOW);
	}
	
    // 네트워크 소켓 설정
    int sock, client_sock;  // 서버의 소켓, 클라이언트와 연결된 소켓
    struct sockaddr_in addr, client_addr; // 서버의 주소, 클라이언트의 주소
    socklen_t addr_len = sizeof(client_addr);
    LED_control_t led_control;  // 클라이언트가 보낸 LED 설정 데이터 저장
    char response[128]; // 데이터를 저장할 공간
	
    // 서버 소켓 생성(socket)
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket ");
		return 1;
	}
    
    // 서버 주소 설정
	memset(&addr, 0x00, sizeof(addr)); // &addr: 서버의 정보를 담는 변수
	addr.sin_family = AF_INET;  // IPv4 주소 체계 사용
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT);    // 서버가 사용하는 포트 번호 설정
	
    // 주소 바인딩(bind)
    // 소켓과 IP/포트를 연결
	if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("bind" );
		return 1;
	}
	
    // 클라이언트 연결 대기(listen)
    // 클라이언트의 연결 요청을 기다리고 최대 5개의 클라이언트를 동시대기시킬 수 있다
	if(listen(sock, 5) < 0) {
		perror("listen ");
		return 1;
	}
	// 클라이언트 연결
    // accept 호출 전, 연결 요청을 받을 준비가 되었음을 출력
	printf("waiting for client..\n");
	
	// 클라이언트 요청 처리
    // accept: 클라이언트의 연결 요청 승인 후 새로운 소켓 생성
	while((client_sock = accept(sock, (struct sockaddr *)&client_addr, &addr_len)) > 0) {
		printf("client ip : %s\n", inet_ntoa(client_addr.sin_addr)); // 연결된 클라이언트의 IP주소 출력
		
        // 클라이언트 데이터 받기(recv)
        // 클라이언트가 보낸 데이터를 led_control에 저장
		recv_len = recv(client_sock,(char*)&led_control, sizeof(led_control_t), 0);
		
		if(recv_len < 0) {
			perror("recv ");
			break;
		}
        
        // 수신 데이터 출력
        printf("Received: LED_NUM=%d, MODE=%d\n", led_control.LED_NUM, led_control.MODE);

		
        // LED 제어 및 상태 업데이트
        if (led_control.LED_NUM < LED_COUNT) {
            if (led_control.MODE == 1) { // LED ON
                digitalWrite(LED_pins[led_control.LED_NUM], HIGH);
                led_states[led_control.LED_NUM] = 1;
                printf("LED %d ON\n", led_control.LED_NUM);
            } else if (led_control.MODE == 0) { // LED OFF
                digitalWrite(LED_pins[led_control.LED_NUM], LOW);
                led_states[led_control.LED_NUM] = 0;
                printf("LED %d OFF\n", led_control.LED_NUM);
            } else {
                printf("Invalid MODE received: %d\n", led_control.MODE);
            }
        } else {
            printf("Invalid LED_NUM received: %d\n", led_control.LED_NUM);
        }

        // 현재 LED 상태를 응답으로 전송
        snprintf(response, sizeof(response), "LED %d is %s", led_control.LED_NUM,(led_states[led_control.LED_NUM] == 1) ? "ON" : "OFF");
        send(client_sock, response, strlen(response), 0);

        close(client_sock); // 클라이언트와 연결 종료
    }

    close(sock); // 서버 소켓 종료
    return 0;
}
	
	
	
	
	
	
	
	
