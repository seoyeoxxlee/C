#include <pthread.h>
#include <stdio.h>

void *threadHello(void *argumentPointer)
{
		while(1) {
			printf("hello\n");
			delay(1000);
			}
		
		return NULL;
}

void *threadBye(void *argumentPointer)
{
		while(1) {
			printf("bye\n");
			delay(1000);
			}
		
		return NULL;
		
}

int main()
{
	pthread_create(NULL, NULL, threadHello, NULL);
	pthread_create(NULL, NULL, threadBye, NULL);
	pthread_join(threadHello, NULL);
	pthread_join(threadBye, NULL);

	return 0;
}
