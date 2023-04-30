# Keylogger - Keystroke Capture

This is a simple project that implements a C++ keystroke capturer, logging keystrokes to a log file. The project has versions for Windows and Linux systems.

## Version for Windows

### Requirements
- Windows
- C++ compiler (like MinGW or Visual Studio)

### Instructions for use
1. Compile the source code using a C++ compiler.
2. Run the resulting program.
3. The program will capture keystrokes and display them on the console.
4. The pressed keys will be recorded in the log file "log.txt" located in "C:\".

**Important**: The use of this program to capture keystrokes may have security and privacy clauses. Use it responsibly and in compliance with applicable laws and regulations.

## Version for Linux

### Requirements
-Linux
- C++ compiler (like GCC)

### Instructions for use
1. Open the source code file "keylogger_linux.cpp" in a text editor.
2. In the indicated code snippet, replace "eventX" with the correct keyboard device number on your system.
3. In the indicated code snippet, adjust the path and name of the log file to the desired location on your system.
4. Compile the source code using the C++ compiler.
5. Run the resulting program with tailored permissions (eg as root) to access the keyboard device and write the log file.
6. The program will capture keystrokes and display them on the console.
7. Keystrokes will be recorded in the specified log file.

**Important**: The use of this program to capture keystrokes may have security and privacy clauses. Use it responsibly and in compliance with applicable laws and regulations.

## Disclaimer

The author of this project is not responsible for any misuse or illegal use of this program. It is the user's responsibility to ensure that the use of this program complies with the laws and regulations overseen in their jurisdiction.