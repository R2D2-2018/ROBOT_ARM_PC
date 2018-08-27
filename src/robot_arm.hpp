/**
 * @file
 * @brief     This file contains the Robot Arm library
 * @author    Jeroen van Hattem
 * @license   See LICENSE
 */
#ifndef ROBOT_ARM_HPP
#define ROBOT_ARM_HPP

#ifdef __WIN32__
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "coordinate3d.hpp"
#include "serial.hpp"
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class RobotArm {
  private:
    Serial connection = Serial("\\\\.\\COM7"); // Windows
    // Serial connection = Serial("/dev/ttyACM0"); // Linux (dmesg | grep tty)
    char gCode[25];
    char response[1024];
    int speed = 50000;
    int clawRotation = 90;
    Coordinate3D currentPosition = Coordinate3D(0, 0, 0);

    /**
     * @brief Create a G-code from coordinates and speed
     *
     * This function creates a G-code from the passed coordinates and speed.
     *
     * @param coordinates
     * @param speed
     */
    void getMoveCode(Coordinate3D coordinates, int speed);
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
     * @return true, if it's safe to move.
     * @return false, it it isn't safe to move.
     */
    bool move(Coordinate3D coordinates, int speed);
    /**
     * @brief Rotate claw
     *
     * This functions rotates the claw to a desired degree.
     *
     * @param value
     * @return true
     * @return false
     */
    bool rotateClaw(int value);
    /**
     * @brief Move X position
     *
     * Move the uArm to a given position in the X direction.
     *
     * @param value
     * @return true, if it's safe to move.
     * @return false, it it isn't safe to move.
     */
    bool moveX(int value);
    /**
     * @brief Move Y position
     *
     * Move the uArm to a given position in the Y direction.
     *
     * @param value
     * @return true, if it's safe to move.
     * @return false, it it isn't safe to move.
     */
    bool moveY(int value);
    /**
     * @brief Move Z position
     *
     * Move the uArm to a given position in the Z direction.
     *
     * @param value
     * @return true, if it's safe to move.
     * @return false, it it isn't safe to move.
     */
    bool moveZ(int value);
    /**
     * @brief Move X position a delta
     *
     * Move the uArm to a delta from current X position.
     *
     * @param value
     * @return true, if it's safe to move.
     * @return false, it it isn't safe to move.
     */
    bool moveDeltaX(int value);
    /**
     * @brief Move Y position a delta
     *
     * Move the uArm to a delta from current Y position.
     *
     * @param value
     * @return true, if it's safe to move.
     * @return false, it it isn't safe to move.
     */
    bool moveDeltaY(int value);
    /**
     * @brief Move Z position a delta
     *
     * Move the uArm to a delta from current Z position.
     *
     * @param value
     * @return true, if it's safe to move.
     * @return false, it it isn't safe to move.
     */
    bool moveDeltaZ(int value);
    /**
     * @brief Reset claw
     *
     * This functions resets the claws rotation and opens it
     *
     */
    void resetClaw();
    /**
     * @brief Close the claw
     *
     * This function closes the claw (if attached)
     *
     */
    void closeClaw();
    /**
     * @brief Open the claw
     *
     * This function opens the claw (if attached)
     *
     */
    void openClaw();
    /**
     * @brief Enable the pump
     *
     * This function enables the pump.
     *
     */
    void enablePump();
    /**
     * @brief Disable the pump
     *
     * This function disables the pump.
     *
     */
    void disablePump();
    /**
     * @brief Reset position
     *
     * This function moves to uArm to a neutral position.
     *
     */
    void resetPosition();
    /**
     * @brief Get the Claw Rotation
     *
     * This function returns the rotation of the claw
     * I was gonna do this by sending "P2206 N3\n" to the uArm, but this doesn't seem to work accordingly.
     *
     * @return int
     */
    int getClawRotation();
    /**
     * @brief Returns the current position
     *
     * This function returns the currentPosition coordinates
     *
     * @return currentCoordinates
     */
    Coordinate3D getCurrentPosition();
    /**
     * @brief Get the position of the arm
     *
     * This function returns the current position of the uArm.
     *
     * @return actualCoordinates
     */
    Coordinate3D getActualPosition();
    /**
     * @brief Checks the state of the claw
     *
     * This function checks the current state of the claw.
     *
     * @return false, claw is open
     * @return true, claw is closed
     */
    bool getClawState();
    /**
     * @brief Checks the state of the pump
     *
     * This function checks the current state of the pump.
     *
     * @return false, pump is open
     * @return true, pump is closed
     */
    bool pumpState();
    /**
     * @brief Is the move safe to do?
     *
     * Are the coordinates passed parameter safe (reachable) to move to?
     * The Z-axis is a very strange thing. Move to somewhere with a reasonable Z, from there go to other values.
     * There's not really much logic in the Z-boundaries.
     * 120  > X < 355
     * -355 > Y < 355
     * 0    > Z < 170
     *
     * @param coordinates
     * @return true
     * @return false
     */
    bool isSafeToMove(Coordinate3D coordinates);
    /**
     * @brief Checks if a command is done
     *
     * This function first calls the readData function, this way the response is updated.
     * Using the response, this function looks for "ok" in the response.
     * This phrase is send by the uArm when a command is succesfully executed.
     * The `state` parameter is used when you want to make the program wait until the robotarm finished something.
     * State 0, wait for the uArm to return "ok". This is returned when a command is received
     * State 1, wait for the uArm to finish moving the arm.
     *
     * @param state
     * @return 0, when not ready
     * @return 1, when ready
     */
    bool commandDone(int state);
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
     * @brief Get the response variable
     *
     * @return char*
     */
    char *getResponse();
    /**
     * @brief Read data from the uArm
     *
     * This function reads data coming from the uArm. This data will be stored in the `response` variable.
     * This way every function can reach it.
     *
     * @return char*
     */
    char *readData();
    /**
     * @brief Wait function
     *
     * A platform independent wait function.
     *
     * @param milliseconds
     */
    void mSleep(int milliseconds);
};

#endif