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
    // RobotArm uArm = RobotArm();
    Serial connection = Serial("\\\\.\\COM7", 115200);
    
    Coordinate3D coordinates = Coordinate3D(150, 150, 80);
    int speed = 50000;

    // sleep(5);
    // std::cout << "Move arm" << std::endl;
    // uArm.move(coordinates, speed);
    // sleep(5);
    // std::cout << "Move Y" << std::endl;
    // uArm.moveY(120);
    // sleep(5);

    // sleep(5);
    // std::cout << "Closing claw" << std::endl;
    // uArm.closeClaw();
    // sleep(5);
    // std::cout << "Move Y" << std::endl;
    // uArm.moveY(120);
    // std::cout << uArm.readData() << std::endl;
    // sleep(5);
    // std::cout << "Opening claw" << std::endl;
    // uArm.openClaw();
    // std::cout << uArm.readData() << std::endl;
    // sleep(5);

    sleep(5);
    connection.writeData("G0 X130 Y150 Z150 F50000\n", 255);
    sleep(5);
    connection.writeData("M2232 V1\n", 255);
    sleep(5);
    connection.writeData("M2232 V0\n", 255);
    sleep(1);

    return 0;
}
