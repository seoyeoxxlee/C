#include <stdio.h> // 화면에 출력하거나 사용자 입력 받음
#include <string.h> // 데이터를 초기화 하고 문자열 다룸
#include <unistd.h> // 파일을 닫거나 다른 기본 작업
#include <sys/types.h>  // 네트워크 통해 서버와 통신
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 3333   // 클라이언트와 서버가 서로 통신하기로 약속한 "문"의 번호

typedef struct {
	unsigned short LED_NUM;
	unsigned short MODE;
} LED_control_t;
	

int main(void) {

	int sock;
	struct sockaddr_in addr;
	LED_control_t led_control;
    
    int send_len;
	char buffer[1024];
	//const char *msg = "helloooooooo"
    
	int recv_len;
	char str[1024];
	
	
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket ");
		return 1;
	}

	memset(&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(PORT);
	
		
	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("connect ");
		return 1;
	}
	
	printf("Insert LED NUMBER(0-3): ");
	scanf("%d", &led_control.LED_NUM);
	printf("LED MODE(0: off, 1: on): ");
	scanf("%d", &led_control.MODE);
	
	send_len = send(sock, (char*)&led_control, sizeof(LED_control_t), 0);
	
	if(send_len < 0) {
		perror("send ");
		return 1;
	}
	
	if((recv_len = recv(sock, buffer, 1024, 0)) < 0) {
		perror("recv ");
		return 1;
	}
	buffer[recv_len] = '\0';
	printf("%s\n", buffer);
	
    close(sock);
	return 0;

}
