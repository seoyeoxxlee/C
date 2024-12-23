// 서버는 누군가 나한테 말을 걸면 대답해주는 프로그램으로,
// 클라이언트가 말을 걸어오면 "그 말 그대로" 다시 돌려주는 역할.
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 3333

int main(void) {
	int sock, client_sock;
	struct sockaddr_in addr, client_addr;
	char buffer[1024];
	int addr_len, recv_len;

	// 소켓 생성
    // 서버도 네트워크 통로를 만들어야 하기 때문에 클라이언트 코드와 마찬가지로 작성.
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket ");
		return 1;
	}
	
    // 서버 주소 설정
    // 클라이언트가 연결할 수 있도록 서버가 자신의 위치를 알려주는 코드.
	memset(&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY); // 이 부분만 클라이언트 코드와 다르니 참고.
	addr.sin_port = htons(PORT);
    
	// 주소와 소켓 연결(bind)
    // 소켓과 주소를 연결하여 클라이언트가 이 주소로 찾아오게끔 설정.
	if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("bind" );
		return 1;
	}
	
    // 클라이언트 대기(listen)
    // 클라이언트를 기다리는 상태로 최대 5명까지 동시에 기다릴 수 있음.
	if(listen(sock, 5) < 0) {
		perror("listen ");
		return 1;
	}
	
	addr_len = sizeof(client_addr);
	printf("waiting for client..\n");
	
    while (1) {
        // 클라이언트 연결 수락
        // 클라이언트가 말을 걸면 연결을 수락함.
        if ((client_sock = accept(sock, (struct sockaddr *)&client_addr, &addr_len)) > 0) {
            printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));

            while (1) {
                // 클라이언트로부터 메시지 받기(recv)
                // 클라이언트가 보낸 메시지를 받음.
                if ((recv_len = recv(client_sock, buffer, sizeof(buffer) - 1, 0)) <= 0) {
                    printf("Client disconnected.\n");
                    break;
                }

                buffer[recv_len] = '\0'; // 받은 메시지 null-terminate
                printf("Client: %s\n", buffer);
                
                // 클라이언트에게 메시지 보내기(send)
                // 받은 메시지 그대로 클라이언트에 전송
                if (send(client_sock, buffer, recv_len, 0) < 0) {
                    perror("send ");
                    break;
                }
            }

            close(client_sock); // 클라이언트 소켓 닫기
        }
    }

    close(sock); // 서버 소켓 닫기
    return 0;
}
