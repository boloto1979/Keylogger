# Keylogger - Keystroke Capture

This is a simple project that implements a keystroke capturer in C++. The project has versions for Windows, Linux, and macOS systems.

## Version for Windows

### Requirements
- Windows
- C++ compiler (such as MinGW or Visual Studio)

### Instructions for Use
1. Compile the source code using a C++ compiler.
2. Run the resulting program.
3. The program will capture keystrokes and display them on the console.
4. The pressed keys will be recorded in the log file "log.txt" located in "C:\".

## Version for Linux

### Requirements
- Linux
- C++ compiler (such as GCC)

### Instructions for Use
1. Open the source code file "keylogger_linux.cpp" in a text editor.
2. In the indicated code snippet, replace "eventX" with the correct keyboard device number on your system.
3. In the indicated code snippet, adjust the path and name of the log file to the desired location on your system.
4. Compile the source code using the C++ compiler.
5. Run the resulting program with appropriate permissions (e.g., as root) to access the keyboard device and write to the log file.
6. The program will capture keystrokes and display them on the console.
7. Keystrokes will be recorded in the specified log file.

## Version for macOS

### Requirements
- macOS
- C++ compiler (such as Xcode Command Line Tools)

### Instructions for Use
1. Open the source code file "keylogger_mac.cpp" in a text editor.
2. In the indicated code snippet, replace "username" with your correct username on the system.
3. Adjust the path and name of the log file to the desired location on your system.
4. Compile the source code using the C++ compiler.
5. Run the resulting program with appropriate permissions to access the keyboard device and write to the log file.
6. The program will capture keystrokes and display them on the console.
7. Keystrokes will be recorded in the specified log file.

## Version with Socket Communication

### Requirements
- Windows, Linux, or macOS
- C++ compiler

### Instructions for Use
1. Open the source code file "keylogger_socket.cpp" in a text editor.
2. Follow the instructions specific to your operating system mentioned in the respective sections above to adjust the code for the keyboard device and log file.
3. Compile the source code using the C++ compiler.
4. Run the resulting program.
5. The program will capture keystrokes and display them on the console.
6. Keystrokes will be recorded in the specified log file.
7. Additionally, the keystrokes will be sent to a socket server with the IP address and port specified in the code.

## Disclaimer

The author of this project is not responsible for any misuse or illegal use of this program. It is the user's responsibility to ensure that the use of this program complies with the laws and regulations of their jurisdiction.
