// 클라이언트 코드는 우리 컴퓨터가 서버에게 말을 거는 프로그램으로
// 내가 하고 싶은 말을 서버에게 보내고, 서버가 그걸 받아서 답장하면 그걸 출력하는 역할.
#include <stdio.h> // 기본 입출력(화면에 글자 출력하거나 입력받는 기능)
#include <string.h> // 문자열을 다룰 때 필요한 기능 제공.
#include <unistd.h> // 컴퓨터 자원을 관리(파일이나 네트워크 소켓 닫기 같은 작업) 하는 기능.
#include <sys/types.h> // 네트워크 소켓을 설정할 때 사용하는 기본적인 데이터 구조 제공.
#include <sys/socket.h> // 네트워크 소켓(컴퓨터 간 연결 통로)을 만들고 관리하는 기능.
#include <netinet/in.h> // 인터넷 주소 처리 기능.
#include <arpa/inet.h> // IP 주소 다룰 때 필요한 기능.

#define PORT 3333

// use char str[1024] instead of *msg to chat with EchoServer..

int main(void) {
	int sock;   // 네트워크 소켓을 저장할 변수로, 네트워크 통로를 열 때 사용.
	struct sockaddr_in addr;    // 서버의 주소를 설정할 구조체. 서버가 어디에 있는지(IP주소와 포트 번호)를 알려줌.
	char buffer[1024];
    char str[1024];
	int recv_len;
	
    // 소켓 생성
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {  // AF_INET: 인터넷(IP) 연결을 사용한다는 뜻.
		perror("socket ");  // SOCK_STREAM: 데이터가 한 줄로 흐르는 방식(TCP)으로 연결하겠다는 뜻.
		return 1;   // 결과적으로 sock이라는 네트워크 통로가 생김.
	}
	
    // 서버 주소 설정
	memset(&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 내 컴퓨터의 IP 주소
	addr.sin_port = htons(PORT);
		
    // 서버에 연결하기 **connect**
    // 클라이언트가 서버에게 대화하자고 요청하는 부분.
	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("connect ");
		return 1;
	}
	
    // 메세지 입력받기(fgets)
    while (1) {
        printf("Insert your message (type 'exit' to quit): ");
        fgets(str, sizeof(str), stdin); // 사용자가 화면에서 입력한 메시지를 읽어오는 코드.
        str[strcspn(str, "\n")] = 0; // 개행 문자 제거

        // 'exit' 입력 시 종료
        if (strcmp(str, "exit") == 0) {
            break;
        }

        // 서버로 메시지 전송(send)
        // 사용자가 입력한 메시지를 서버로 보냄.
        if (send(sock, str, strlen(str), 0) < 0) {
            perror("send ");
            break;
        }

        // 서버의 응답받기(recv)
        // 서버가 보낸 메시지를 받아서 buffer에 저장.
        if ((recv_len = recv(sock, buffer, sizeof(buffer) - 1, 0)) < 0) {
            perror("recv ");
            break;
        }

        // 받은 메시지 출력.
        buffer[recv_len] = '\0'; // 받은 메시지 null-terminate
        printf("Server: %s\n", buffer);
    }

    close(sock); // 소켓 닫기
    return 0;
}
