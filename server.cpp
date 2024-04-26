#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

int main() 
{
    // Создание сокета
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error: Failed to create socket\n";
        return 1;
    }

    // Настройка адреса сервера
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080); // Порт 8080

    // Привязка сокета к адресу и порту
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error: Failed to bind socket(\n";
        return 1;
    }

    // Прослушивание входящих соединений
    if (listen(serverSocket, 10) < 0) {
        std::cerr << "Error: Failed to listen on socket(\n";
        return 1;
    }

    std::cout << "Server is listening on port 8080...\n";

    // Принятие входящих соединений
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    if (clientSocket < 0) {
        std::cerr << "Error: Failed to accept connection\n";
        return 1;
    }

    std::cout << "Client connected)\n";

    // Отправка сообщения клиенту
    const char* message = "Hello from server!";
    send(clientSocket, message, strlen(message), 0);

    // Закрытие сокетов
    close(clientSocket);
    close(serverSocket);

    return 0;
}

