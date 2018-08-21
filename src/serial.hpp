/**
 * @file
 * @brief     This file contains the Seriallibrary
 * @author    Jeroen van Hattem
 * @license   See LICENSE
 */
#ifndef SERIAL_HPP
#define SERIAL_HPP

#define ARDUINO_WAIT_TIME 2000

#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#ifdef _WIN32
    #include <windows.h>
    
    // For more info about the Windows part: http://playground.arduino.cc/Interfacing/CPPWindows
    class Serial {
        private:
            HANDLE hSerial;
            bool connected;
            COMSTAT status;
            DWORD errors;

        public:
            /**
             * @brief Construct a new Serial object
             * 
             * @param portName 
             */
            Serial(const char *portName);
            /**
             * @brief Destroy the Serial object
             * 
             */
            ~Serial();
            /**
             * @brief Read data from uArm.
             * 
             * This functions reads data from the uArm. The read data will be stored in the buffer parameter. Returns -1 if nothing could be read.
             * 
             * @param buffer 
             * @param size 
             * @return int 
             */
            int readData(char *buffer, unsigned int size);
            /**
             * @brief Write data to the uArm.
             * 
             * This function writes "size" bytes of data to the uArm. When the data is sent succesfully, true will be returned.
             * 
             * @param buffer 
             * @param size 
             * @return true 
             * @return false 
             */
            bool writeData(const char *buffer, unsigned int size);
            /**
             * @brief Check if we're connected with the Robot Arm.
             * 
             * This functions returns a boolean value depending on whether or not we're connected to the uArm.
             * 
             * @return true 
             * @return false 
             */
            bool isConnected();


    };
#endif // Windows

#ifdef __unix
    #include <errno.h> /* ERROR Number Definitions           */
    #include <fcntl.h> /* File Control Definitions           */
    #include <termios.h> /* POSIX Terminal Control Definitions */
    #include <unistd.h>  /* UNIX Standard Definitions 	   */

    class Serial {
    private:
        bool connected;
        int file;
        std::string string_value;

    public:
        /**
         * @brief Construct a new Serial object
         * 
         * @param portName 
         */
        Serial(const char *portName);
        /**
         * @brief Destroy the Serial object
         * 
         */
        ~Serial();
        /**
         * @brief Read data from uArm.
         * 
         * This functions reads data from the uArm. The read data will be stored in the buffer parameter.
         * 
         * @param buffer 
         * @param size 
         * @return int 
         */
        int readData(char *buffer, unsigned int size);
        /**
         * @brief Write data to uArm.
         * 
         * This function writes "size" bytes of data to the uArm. When the data is sent succesfully, true will be returned.
         * 
         * @param buffer 
         * @param size 
         * @return true 
         * @return false 
         */
        bool writeData(const char *buffer, unsigned int size);
        /**
         * @brief Check if we're connected with the Robot Arm.
         * 
         * This functions returns a boolean value depending on whether or not we're connected to the uArm.
         * 
         * @return true 
         * @return false 
         */
        bool isConnected();
    };
#endif // Linux

#endif // SERIAL_HPP