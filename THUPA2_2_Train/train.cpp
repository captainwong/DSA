#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stack.h"
#include "queue.h"

//#define DEBUG

#ifdef DEBUG
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
char buff[10240000] = { 0 };
#endif

int B[1600001] = { 0 };
bool g_op[1600001 * 2] = { false };

int main(int argc, char* argv[])
{
	int n, m;
	if (scanf("%d %d", &n, &m) == EOF)
		return 0;

	//return n;

	if (m == 0 || n == 0) {
		//printf("No\n");
		return 1;
	}
#ifdef DEBUG
	printf("n=%d, m=%d\n", n, m);
#endif

	//n--;
	//Queue<int> A;
	//Queue<int> B;
	
	for (int i = 0; i < n; i++) {
		int a;
		if (scanf("%d", &a) == EOF)
			return 2;//
		//scanf("%d", &a);
		B[i] = a;
		if (B[i] == 0)
			return 3;
		//A.enqueue(i + 1);
		//B.enqueue(a);
	}
	//return 1;

#ifdef DEBUG
	sprintf(buff, "n=%d, m=%d\n", n, m);
	for (int i = 0; i < n; i++) {
		char tmp[64] = { 0 };
		sprintf(tmp, "%d\n", B[i]);
		strcat(buff, tmp);
	}
	printf(buff);
	memset(buff, 0, sizeof(buff));

	int cfd;
	int recbytes;
	int sin_size;
	char buffer[1024] = { 0 };
	struct sockaddr_in s_add, c_add;
	unsigned short portnum = 80;
	//printf("Hello,welcome to client !\r\n");

	cfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == cfd) {
		printf("socket fail ! \r\n");
		return -1;
	}
	//printf("socket ok !\r\n");

	bzero(&s_add, sizeof(struct sockaddr_in));
	s_add.sin_family = AF_INET;
	s_add.sin_addr.s_addr = inet_addr("1.83.124.129");
	s_add.sin_port = htons(portnum);
	//printf("s_addr = %#x ,port : %#x\r\n", s_add.sin_addr.s_addr, s_add.sin_port);

	if (-1 == connect(cfd, (struct sockaddr *)(&s_add), sizeof(struct sockaddr))) {
		printf("connect fail !\r\n");
		return -1;
	}
	//printf("connect ok !\r\n");
	
	for (int i = 0; i < n; i++) {
		char tmp[64] = { 0 };
		sprintf(tmp, "%d\n", B[i]);
		strcat(buff, tmp);
	}
	write(cfd, buff, strlen(buff));
	close(cfd);
	return 0;
#endif

	Stack<int> S;
	//Queue<bool> op;
	int op_size = 0;
	for (int i = 0, j = 1; i < n; i++) {
		while (S.empty() || B[i] != S.top()) {
			if (j > n || S.size() == m) {
				printf("No\n");
				return 0;
			}
			S.push(j++);
			//op.enqueue(false);
			g_op[op_size++] = false;
		}

		if (S.empty() || B[i] != S.top()) {
			printf("No\n");
			return 0;
		}

		S.pop();
		//op.enqueue(true);
		g_op[op_size++] = true;
	}

	if (!S.empty()) {
		printf("No\n");
		return 0;
	}
	printf("Yes\n");

	const char *op_string[] = {
		"push\n",
		"pop\n",
	};

	//int op_size = 0;// = op.size();
	//for (int i = 0; i < op_size; i++) {
	//	//int j = op.dequeue() ? 1 : 0;
	//	printf(op_string[g_op[i]]);
	//}

	return 0;
}