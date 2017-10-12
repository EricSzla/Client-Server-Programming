#include "unp.h"
#include <time.h>

int main(int argc, char **argv)
{
	int listenfd, connfd;
	int listenfd2, connfd2;
	int n, m;
	struct sockaddr_in servaddr, servaddr2;
	char buff[MAXLINE + 1];
	char buff2[MAXLINE + 1];
	char initialBuff[MAXLINE + 1];

	if(argc != 3)
		err_quit("usage: <Program Name> <Port No.>");

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	listenfd2 = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	bzero(&servaddr2, sizeof(servaddr2));

	servaddr.sin_family = 		AF_INET;
	servaddr.sin_addr.s_addr = 	htonl(INADDR_ANY);
	servaddr.sin_port = 		htons(atoi(argv[1]));
	
	servaddr2.sin_family = 		AF_INET;
	servaddr2.sin_addr.s_addr =	htonl(INADDR_ANY);
	servaddr2.sin_port =		htons(atoi(argv[2]));

	
	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
	Listen(listenfd, LISTENQ);

	Bind(listenfd2, (SA *) &servaddr2, sizeof(servaddr2));
	Listen(listenfd2, LISTENQ);

	for( ; ; )
	{
		// Trying to establish connection with port 1
		connfd = Accept(listenfd, (SA *) NULL, NULL);
		char msg[MAXLINE];
		strcpy(msg, "Waiting for connection...");
		snprintf(buff, sizeof(buff), "%.24s\r\n", msg);
		Write(connfd, buff, strlen(buff));
		
		// Waiting to establish connection with port 2
		connfd2 = Accept(listenfd2, (SA *) NULL, NULL);
		msg[0] = 0;
		// Connection established, inform the two users
		strcpy(msg,"Connection Established!");
		snprintf(buff,sizeof(buff), "%.42s\r\n", msg);
		Write(connfd,buff,strlen(buff));
		Write(connfd2,buff,strlen(buff));
		
		// While the connection is aviable then we can communicate
		while(connfd > 0 && connfd2 > 0){
			printf("waiting to read client 1\r\n");
			snprintf(initialBuff, sizeof(initialBuff),"QwErTy");
			Write(connfd,initialBuff,strlen(initialBuff));
			while( (n = read(connfd,buff2, MAXLINE)) > 0) {
				buff2[n] = 0;
				printf("waiting for client2\r\n");
				snprintf(msg, sizeof(msg), "%.24s\r\n",buff2);
				Write(connfd2, msg, strlen(msg));
				printf("sent data to client 2\r\n");
				break;
			}
			printf("Should be after sent data..\r\n");
			snprintf(initialBuff, sizeof(initialBuff),"QwErTy");
			Write(connfd2,initialBuff,strlen(initialBuff));
			printf("waiting to read client2\r\n");
			while( (m = read(connfd2, buff, MAXLINE)) > 0) {
				buff[m] = 0;
				printf("waiting for client1\r\n");
				snprintf(msg,sizeof(msg), "%.24s\r\n",buff);
				Write(connfd, msg, strlen(msg));
				break;
			}
		}
		printf("outside the read/write loop\r\n");
		msg[0] = '\0';
		strcpy(msg, "Conneciton lost..");
		snprintf(buff,sizeof(buff), "%.24s\r\n", msg);
	
		if(connfd > 0 && connfd <= 0)
			Write(connfd,buff,strlen(buff));

		if(connfd <= 0 && connfd > 0)
			Write(connfd2, buff,strlen(buff));

		Close(connfd);
		Close(connfd2);
	}
}

