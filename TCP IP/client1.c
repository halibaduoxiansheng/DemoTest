#include <stdio.h>
#include <winsock.h>
#include <string.h>
#include <stdlib.h>
#include <process.h>
#pragma comment(lib,"ws2_32.lib")

#define SERVER_IP "192.168.73.1"
#define PORT 5000

void __cdecl receiveThread(void* arg) {
    SOCKET serverSocket = (SOCKET)arg;
    char recvBuf[100];
    int recvLen;

    while (1) {
        memset(recvBuf, 0, sizeof(recvBuf));
        recvLen = recv(serverSocket, recvBuf, sizeof(recvBuf) - 1, 0);
        if (recvLen > 0) {
            printf("Server says: %s\n", recvBuf);
        } else if (recvLen == 0) {
            printf("Server disconnected.\n");
            break;
        } else {
            printf("Receive error.\n");
            break;
        }
    }
    closesocket(serverSocket);
    _endthread();
}

int main(void) {
    WSADATA wsaData;
    SOCKET clientSocket;
    SOCKADDR_IN serverAddr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    int error;

    error = WSAStartup(wVersionRequested, &wsaData);
    if (error != 0) {
        printf("WSAStartup failed.\n");
        return 1;
    }

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        WSACleanup();
        printf("Unsupported version.\n");
        return 1;
    }

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        printf("Socket creation failed.\n");
        WSACleanup();
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(PORT);

    if (connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Connect failed.\n");
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    printf("Connected to server.\n");

    _beginthread(receiveThread, 0, (void*)clientSocket);

    char sendBuf[100];
    int sendLen;

    while (1) {
        printf("Enter message to send (type 'exit' to quit): ");
        scanf("%99s", sendBuf);

        if (strcmp(sendBuf, "exit") == 0) {
            break;
        }

        sendLen = send(clientSocket, sendBuf, strlen(sendBuf), 0);
        if (sendLen == SOCKET_ERROR) {
            printf("Send failed.\n");
            break;
        }
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
