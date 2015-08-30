#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <conio.h>
#include "struct_header.h"

#pragma comment(lib,"wsock32.lib")
#define SEND_COUNT   10

void ErrorHandling(char *message);
void SocketOpen();

void main(void)
{
	int ch=NULL;

	while(1)
	{
		printf("\n[1]전송,[2],종료\n");
		ch=getch();

		switch(ch)
		{
			case'1':
				SocketOpen();
				break;
			case'2':
				return;
			default:
				puts("[1]전송,[2],종료");
				break;
		}
	}
	return;
}

void ErrorHandling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}

void SocketOpen()
{
	WSADATA wsaData;
	SOCKET hSocket;
	int strLen;
	int i;
	
	SOCKADDR_IN servAddr;

	if(WSAStartup(MAKEWORD(2,2),&wsaData) != 0)
		ErrorHandling("WSAStratup() error!");

	hSocket=socket(PF_INET,SOCK_STREAM,0);
	if(hSocket==INVALID_SOCKET)
		ErrorHandling("socket() error");
									   
	memset(&servAddr,0,sizeof(servAddr));						
	servAddr.sin_family=AF_INET;
	servAddr.sin_addr.s_addr=inet_addr("211.227.151.169");
	servAddr.sin_port=htons(2000);

	if(connect(hSocket,(SOCKADDR *)&servAddr,sizeof(servAddr))==SOCKET_ERROR)
		ErrorHandling("connect() error");

	MsgBuff msg;
	char sendData[MSG_SiZE + MSG_HEADER];
	int count=1;

	while(1)
	{
		memset(&msg, 0x00, sizeof(msg));
		memset(&sendData, 0x00, sizeof(sendData));

		msg.data_sz = sizeof(msg);
		msg.msgID = count;

		memcpy(&msg.data[0], "1", 1);
		memcpy(&msg.data[1], "123", 3);

		memcpy(&sendData, &msg, sizeof(msg));
		Sleep(1);
		send(hSocket, sendData, MSG_SiZE+MSG_HEADER, 0);
		
		printf("%d\n", msg.msgID);
		count++;
	}
	
	closesocket(hSocket);
	WSACleanup();
	return;
}	
