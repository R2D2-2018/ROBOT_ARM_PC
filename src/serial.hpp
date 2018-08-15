#ifndef SERIAL_HPP
#define SERIAL_HPP

#define ARDUINO_WAIT_TIME 2000

#ifdef _WIN32
    #include <windows.h>
    #include <stdio.h>
    #include <iostream>
    #include <stdlib.h>
    #include <string>
    class Serial {
        private:
            //Serial comm handler
            HANDLE hSerial;
            //Connection status
            bool connected;
            //Get various information about the connection
            COMSTAT status;
            //Keep track of last error
            DWORD errors;

        public:
            //Initialize Serial communication with the given COM port
            Serial(const char *portName);
            //Close the connection
            ~Serial();
            //Read data in a buffer, if nbChar is greater than the
            //maximum number of bytes available, it will return only the
            //bytes available. The function return -1 when nothing could
            //be read, the number of bytes actually read.
            int readData(char *buffer, unsigned int size);
            //Writes data from a buffer through the Serial connection
            //return true on success.
            bool writeData(const char *buffer, unsigned int size);
            //Check if we are actually connected
            bool isConnected();


    };
#endif // Windows

#ifdef __unix
    #include <stdio.h>
    #include <iostream>
    #include <stdlib.h>
    #include <string>
    #include <errno.h> /* ERROR Number Definitions           */
    #include <fcntl.h> /* File Control Definitions           */
    #include <termios.h> /* POSIX Terminal Control Definitions */
    #include <unistd.h>  /* UNIX Standard Definitions 	   */

    class Serial {
        private:
        std::string string_value;

    public:
        int file;
        Serial(const char *portName);
        int readData(char *buffer, unsigned int size);
        void writeData(const char *buffer, unsigned int size);
    };
#endif // Linux

#endif // SERIAL_HPP