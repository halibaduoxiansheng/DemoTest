#include <stdio.h>
#include <winsock.h>
#include <string.h>
#include <stdlib.h>
#include <process.h>
#pragma comment(lib,"ws2_32.lib")

#define PORT 5000

void __cdecl receiveThread(void* arg) {
    SOCKET clientSocket = (SOCKET)arg;
    char recvBuf[100];
    int recvLen;

    while (1) {
        memset(recvBuf, 0, sizeof(recvBuf));
        recvLen = recv(clientSocket, recvBuf, sizeof(recvBuf) - 1, 0);
        if (recvLen > 0) {
            printf("Client says: %s\n", recvBuf);
        } else if (recvLen == 0) {
            printf("Client disconnected.\n");
            break;
        } else {
            printf("Receive error.\n");
            break;
        }
    }
    closesocket(clientSocket);
    _endthread();
}

int main(void) {
    WSADATA wsaData;
    SOCKET listenSocket, clientSocket;
    SOCKADDR_IN serverAddr, clientAddr;
    int clientAddrSize = sizeof(clientAddr);
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

    listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket == INVALID_SOCKET) {
        printf("Socket creation failed.\n");
        WSACleanup();
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(PORT);

    if (bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Bind failed.\n");
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    if (listen(listenSocket, 1) == SOCKET_ERROR) {
        printf("Listen failed.\n");
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    printf("Waiting for client...\n");
    clientSocket = accept(listenSocket, (SOCKADDR*)&clientAddr, &clientAddrSize);
    if (clientSocket == INVALID_SOCKET) {
        printf("Accept failed.\n");
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    printf("Client connected.\n");

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
    closesocket(listenSocket);
    WSACleanup();
    return 0;
}
