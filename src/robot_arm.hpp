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
    /**
     * @brief Move X position
     * 
     * Move the uArm to a given position in the X direction.
     * 
     * @param value 
     */
    void moveX(int value);
    /**
     * @brief Move Y position
     * 
     * Move the uArm to a given position in the Y direction.
     * 
     * @param value 
     */
    void moveY(int value);
    /**
     * @brief Move Z position
     * 
     * Move the uArm to a given position in the Z direction.
     * 
     * @param value 
     */
    void moveZ(int value);
    /**
     * @brief Close the claw
     * 
     * This function closes the claw (if attached)
     * 
     */
    void closeClaw();
    /**
     * @brief Reset position
     * 
     * This function moves to uArm to a neutral position.
     * 
     */
    void resetPosition();
    /**
     * @brief Open the claw
     * 
     * This function opens the claw (if attached)
     * 
     */
    void openClaw();
    /**
     * @brief Store the coordinates
     * 
     * This function stores the location pass as parameter in a local variable.
     * 
     * @param coordinates 
     */
    void saveCoordinates(Coordinate3D coordinates);
    /**
     * @brief Store the speed
     * 
     * Store the speed passed as parameter in a local variable.
     * 
     * @param speed 
     */
    void saveSpeed(int speed);
    /**
     * @brief Send data to the serial connection
     * 
     * This function send a string of `x` size to the uArm.
     * 
     * @param command 
     * @param size 
     */
    void writeData(const char *command, unsigned int size);
    /**
     * @brief Checks if a command is done
     * 
     * This function first calls the readData function, this way the response is updated.
     * Using the response, this function looks for "ok" in the response. 
     * This phrase is send by the uArm when a command is succesfully executed.
     * 
     * @return true 
     * @return false 
     */
    bool commandDone();
    /**
     * @brief Read data from the uArm
     * 
     * This function reads data coming from the uArm. This data will be stored in the `response` variable. 
     * This way every function can reach it.
     * 
     * @return char* 
     */
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
};

#endif