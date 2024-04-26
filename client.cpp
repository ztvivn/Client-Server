#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main() 
{
    // Создание сокета
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error: Failed to create socket\n";
        return 1;
    }

    // Настройка адреса сервера
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080); // Порт 8080
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP-адрес сервера

    // Подключение к серверу
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error: Failed to connect to server\n";
        return 1;
    }

    std::cout << "Connected to server\n";

    // Получение сообщения от сервера
    char buffer[1024] = {0};
    recv(clientSocket, buffer, 1024, 0);
    std::cout << "Server: " << buffer << std::endl;

    // Закрытие сокета
    close(clientSocket);

    return 0;
}

