/**
 * @file
 * @brief     This file contains the Robot Arm library
 * @author    Jeroen van Hattem
 * @license   See LICENSE
 */
#ifndef ROBOT_ARM_HPP
#define ROBOT_ARM_HPP

#include "coordinate3d.hpp"
#include "serial.hpp"
#include <iostream>

class RobotArm {
private:
    Serial connection = Serial("\\\\.\\COM7");
    char gCode[25];
    int MESSAGE_SIZE = 255;
    int xPosition = 120;
    int yPosition = 120;
    int zPosition = 120;
    int speed = 50000;
    char response[1024];
public:
    /**
     * @brief Construct a new Robot Arm object
     * 
     */
    RobotArm();
    /**
     * @brief Function to move the arm
     * 
     * This function is used to move the arm to a new location
     * 
     * @param coordinates 
     * @param speed 
     */
    void move(Coordinate3D coordinates, int speed);
    void moveX(int value);
    void moveY(int value);
    void moveZ(int value);
    void closeClaw();
    void openClaw();
    void saveCoordinates(Coordinate3D coordinates);
    void saveSpeed(int speed);
    void writeData(const char *command, unsigned int size);
    bool commandDone();
    char* readData();
    /**
     * @brief Create a G-code from coordinates and speed
     * 
     * This function creates a G-code from the passed coordinates and speed.
     * 
     * @param coordinates 
     * @param speed 
     */
    void createGCode(Coordinate3D coordinates, int speed);
    /**
     * @brief intToChar function
     *
     * This function takes an integer number and converts it to a char *. The char * will be stored in the 'dest'(destination)
     * parameter
     *
     * @param x : int
     * @param dest  : char *
     * @return char*
     */
    char *intToChar(int x, char *dest);

    /**
     * @brief strcopy function
     *
     * This function is purely here because the STD variant doesn't work. It's a literal copy of strcpy. dest = destination. src =
     * source.
     *
     * @param dest : char *
     * @param src : const char *
     * @return char*
     */
    char *strcopy(char *dest, const char *src);

    /**
     * @brief stradd function
     *
     * This function is purely here because the STD variant doesn't work. It's a literal copy of strcat. dest = destination. src =
     * source.
     *
     * @param dest : char *
     * @param src : const char *
     * @return char*
     */
    char *stradd(char *dest, const char *src);
};

#endif