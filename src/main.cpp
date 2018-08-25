/**
 * @file
 * @brief     The Robot Arm module for PC
 * @author    Jeroen van Hattem
 * @license   See LICENSE
 */
#include "robot_arm.hpp"
#include <iostream>

int main() {
    RobotArm uArm = RobotArm();

    Coordinate3D coordinates = Coordinate3D(150, 150, 100);
    int speed = 50000;

    std::cout << "RESETTING" << std::endl;

    uArm.resetPosition();
    while (!uArm.commandDone(1)) {
    }

    uArm.move(coordinates, speed);
    while (!uArm.commandDone(1)) {
    }

    if (uArm.getCurrentPosition() == uArm.getActualPosition()) {
        std::cout << "Waiting for moving succesfull" << std::endl;
    } else {
        std::cout << "Waiting for moving unsuccesfull" << std::endl;
    }

    coordinates = Coordinate3D(1000, 300, 100);
    if (!uArm.move(coordinates, speed)) {
        std::cout << "Safety Bouds succesfull" << std::endl;
    } else {
        std::cout << "Safety Bouds unsuccesfull" << std::endl;
    }

    uArm.moveX(200);
    while (!uArm.commandDone(1)) {
    }

    if (uArm.getCurrentPosition() == uArm.getActualPosition()) {
        std::cout << "X position succesfull" << std::endl;
    } else {
        std::cout << "X position unsuccesfull" << std::endl;
    }

    uArm.moveY(150);
    while (!uArm.commandDone(1)) {
    }

    if (uArm.getCurrentPosition() == uArm.getActualPosition()) {
        std::cout << "Y position succesfull" << std::endl;
    } else {
        std::cout << "Y position unsuccesfull" << std::endl;
    }

    uArm.moveZ(80);
    while (!uArm.commandDone(1)) {
    }

    if (uArm.getCurrentPosition() == uArm.getActualPosition()) {
        std::cout << "Z position succesfull" << std::endl;
    } else {
        std::cout << "Z position unsuccesfull" << std::endl;
    }

    uArm.moveDeltaX(-10);
    while (!uArm.commandDone(1)) {
    }

    if (uArm.getCurrentPosition() == uArm.getActualPosition()) {
        std::cout << "Delta X position succesfull" << std::endl;
    } else {
        std::cout << "Delta X position unsuccesfull" << std::endl;
    }

    uArm.moveDeltaY(10);
    while (!uArm.commandDone(1)) {
    }

    if (uArm.getCurrentPosition() == uArm.getActualPosition()) {
        std::cout << "Delta Y position succesfull" << std::endl;
    } else {
        std::cout << "Delta Y position unsuccesfull" << std::endl;
    }

    uArm.moveDeltaZ(10);
    while (!uArm.commandDone(1)) {
    }

    if (uArm.getCurrentPosition() == uArm.getActualPosition()) {
        std::cout << "Delta Z position succesfull" << std::endl;
    } else {
        std::cout << "Delta Z position unsuccesfull" << std::endl;
    }

    std::cout << "RESETTING" << std::endl;

    uArm.resetPosition();
    while (!uArm.commandDone(1)) {
    }

    uArm.rotateClaw(180);
    std::cout << "Claw rotation: " << uArm.getClawRotation() << std::endl;

    uArm.rotateClaw(0);
    std::cout << "Claw rotation: " << uArm.getClawRotation() << std::endl;

    uArm.closeClaw();
    uArm.mSleep(2000);
    std::cout << "Claw state: " << uArm.getClawState() << std::endl;

    uArm.openClaw();
    uArm.mSleep(2000);
    std::cout << "Claw state: " << uArm.getClawState() << std::endl;

    uArm.enablePump();
    uArm.mSleep(1000);
    std::cout << "Pump state: " << uArm.pumpState() << std::endl;

    uArm.disablePump();
    uArm.mSleep(1000);
    std::cout << "Pump state: " << uArm.pumpState() << std::endl;

    return 0;
}
