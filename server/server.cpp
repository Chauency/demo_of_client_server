//�ο����ͣ� http://blog.csdn.net/gneveek/article/details/8699198
#include "stdafx.h"
#include <iostream>
#include <Winsock2.h>
#pragma comment(lib,"ws2_32.lib") 
//��仰��ǰ����˼�Ǿ�̬����һ��lib�ļ�Ҳ���ǿ��ļ� ws2_32.lib�ļ����ṩ�˶������������API��֧�֣���ʹ�����е�API����Ӧ�ý�ws2_32.lib���빤�̣�������Ҫ��̬����ws2_32.dll����
//��仰һ��������������У���Ҫʹ������API������ʱ�򣬾ͱ���ʹ������������ws2_32.lib����߶�̬����ws2_32.dll
using namespace std;
int main(int argc, _TCHAR* argv[])
{
	WORD sockVersion = MAKEWORD(2,2);
	WSADATA wsaData;

	if(WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}
	// int socket(int domain, int type, int protocol);
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(slisten == INVALID_SOCKET)
	{
		cout << "socket error!\n";
		return 0;
	}


	//sockaddr_in��һ���ṹ��
	//struct sockaddr_in {
    //sa_family_t    sin_family; /* address family: AF_INET */
    //in_port_t      sin_port;   /* port in network byte order */
    //struct in_addr sin_addr;   /* internet address */
	//};

	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;

	//bind()������һ����ַ���е��ض���ַ����socket
	if(bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		cout << "bind error!\n";
		return 0;
	}

	if(listen(slisten, 5) == SOCKET_ERROR)
	{
		cout << "listen error!\n";
	}

	SOCKET sClient;
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	char revData[255];
	while(1)
	{
		cout << "waiting connect...\n";
		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
		if(sClient == INVALID_SOCKET)
		{
			cout << "accept error!";
			continue;
		}
		cout << "accept a connection:\n" << inet_ntoa(remoteAddr.sin_addr)  << endl;

		//receiving
		int ret = recv(sClient, revData, 255, 0);
		if(ret > 0)
		{
			revData[ret] = 0x00;
			cout << revData << endl;
		}
		const char * sendData = "Hello, TCP client!";
		send(sClient, sendData, strlen(sendData), 0);
		closesocket(sClient);

	}
	closesocket(slisten);
	WSACleanup();
	return 0;
}

