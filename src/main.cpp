/**
 * @file
 * @brief     The Robot Arm module for PC
 * @author    Jeroen van Hattem
 * @license   See LICENSE
 */
#include <iostream>
#include "robot_arm.hpp"
#include "serial.hpp"
#include <unistd.h> // Sleep function

#define DATA_LENGTH 255

int main() {
    RobotArm uArm = RobotArm();
    
    Coordinate3D coordinates = Coordinate3D(180, 150, 150);
    int speed = 50000;

    sleep(2); // Wait until the serial connection is set up and the uArm responds.

    std::cout << "Moving" << std::endl;
    uArm.move(coordinates, speed);
    while(!uArm.commandDone());

    std::cout << "Closing claw" << std::endl;
    uArm.closeClaw();
    while(!uArm.commandDone());

    std::cout << "Resetting position" << std::endl;
    uArm.resetPosition();
    while(!uArm.commandDone());

    std::cout << "Opening claw" << std::endl;
    uArm.openClaw();
    while(!uArm.commandDone());

    return 0;
}
