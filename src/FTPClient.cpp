/*
FTPClient.cpp
*/
#include "FTPClient.h"

using namespace std;

void FTPClient::Connect(int port, char *adr) {
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	inet_pton(AF_INET, adr, &saddr.sin_addr.s_addr);
	if (connect(sock, (struct sockaddr*)(&saddr), sizeof(saddr)) != 0) {
		cout << "No connection established." << endl;
		exit(1);
	}
	cout << "\nConnected to server on IP " << adr << " and port " << port << "." << endl;
}

void FTPClient::SendMsg(char msg[], int size) {
	if (send(sock, msg, size, 0) == -1) {
		cout << "Could not send message to server." << endl;
		exit(1);
	}
	cout << "Sent to server:\t\t";
	cout << msg;
}

char* FTPClient::RecvMsg() {
	cout << "Received from server:\t";

	int x;
	char received[1024];
	x = recv(sock, received, 1024, 0); //recv() returns length of message
	received[x] = '\0'; //0 indexing
	cout << received;
	return received;
}

void FTPClient::SaveFile(char filename[]) {
	ofstream file;
	file.open(filename);
	char buffer[1];
	int bytes(0);
	cout << "/*****FIRST 1 KB OF FILE**********************************************************************/" << endl;
	while (recv(sock, buffer, sizeof(buffer), 0)) {
		if (bytes < 1024)
			cout << buffer[0];
		file << buffer[0];
		bytes++;
	}
	cout << "\n/*********************************************************************************************/" << endl;
	file.close();
}

/*void FTPClient::CloseCon() {
	closesocket(sock);
	WSACleanup();
	cout << "Closed connection.\n" << endl;
}
*/