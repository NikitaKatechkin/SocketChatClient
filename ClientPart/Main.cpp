#include <iostream>

#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <WS2tcpip.h>

const int MSG_MAX_LENGTH = 256;

SOCKET Connection;

/*void ConnectionHandler(SOCKET Connection)
{
	char msg[256];
	while (true)
	{
		recv(Connection, msg, sizeof(msg), NULL);
		std::cout << msg << std::endl;
	}
}*/

void ConnectionHandler()
{
	char msg[MSG_MAX_LENGTH];
	while (true)
	{
		recv(Connection, msg, sizeof(msg), NULL);
		std::cout << msg << std::endl;
	}
}

int main(int argc, char* argv[])
{
	//Library download
	WSADATA wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		std::cout << "ERROR ";
		std::cout << ">> Can not get WinSock2 appropriate version" << std::endl;
		exit(1);
	}

	//SOCKADDR_IN stores address
	//*_IN because of INTERNET 
	//Configures info ABOUT socket in Network
	SOCKADDR_IN addr;
	inet_pton(AF_INET, "127.0.0.1\0", &addr.sin_addr.s_addr); //IP-address: 127.0.0.1
	addr.sin_port = htons(1111); //Port: 1111
	addr.sin_family = AF_INET; //Socket family: AF_INET
	int addr_size = sizeof(addr);
	//END OF SOCKADDR_IN CONFIGURATION

	//Creates socket
	//Socket family: AF_INET (Internet protocol)
	//Socket type: SOCK_STREAM (TCP protocol)
	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	
	if (connect(Connection, (SOCKADDR *)&addr, addr_size) != 0)
	{
		std::cout << "ERROR" << std::endl;
		std::cout << "Can not create connection to server" << std::endl;
		return 1;
	}
	std::cout << "Succesfully Connected to server" << std::endl;

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ConnectionHandler, NULL, NULL, NULL);

	char msg1[MSG_MAX_LENGTH];
	while (true)
	{
		std::cin.getline(msg1, sizeof(msg1));
		send(Connection, msg1, sizeof(msg1), NULL);
		Sleep(10);
	}


	system("pause");
	return 0;
}