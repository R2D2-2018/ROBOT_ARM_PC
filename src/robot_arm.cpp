/**
 * @file
 * @brief     This file contains the Robot Arm library
 * @author    Jeroen van Hattem
 * @license   See LICENSE
 */
#include "robot_arm.hpp"

RobotArm::RobotArm() {
    strcpy(gCode, "P2202\n"); // Send a command to ensure the connection is working. This should return the hardware version.
    writeData(gCode, sizeof(gCode));
}

void RobotArm::move(Coordinate3D coordinates, int speed) {
    createGCode(coordinates, speed);
    saveCoordinates(coordinates);
    saveSpeed(speed);
    std::cout << gCode << std::endl;
    writeData(gCode, sizeof(gCode));
}

void RobotArm::moveX(int value) {
    xPosition = value;
    Coordinate3D coordinates = Coordinate3D(value, yPosition, zPosition);
    createGCode(coordinates, speed);
    writeData(gCode, sizeof(gCode));
}

void RobotArm::moveY(int value) {
    yPosition = value;
    Coordinate3D coordinates = Coordinate3D(xPosition, value, zPosition);
    createGCode(coordinates, speed);
    writeData(gCode, sizeof(gCode));
}

void RobotArm::moveZ(int value) {
    zPosition = value;
    Coordinate3D coordinates = Coordinate3D(xPosition, yPosition, value);
    createGCode(coordinates, speed);
    writeData(gCode, sizeof(gCode));
}

void RobotArm::resetPosition() {
    strcpy(gCode, "G0 X150 Y0 Z0 F50000\n");
    writeData(gCode, sizeof(gCode));
}

void RobotArm::closeClaw() {
    strcpy(gCode, "M2232 V1\n");
    writeData(gCode, sizeof(gCode));
}

void RobotArm::openClaw() {
    strcpy(gCode, "M2232 V0\n");
    writeData(gCode, sizeof(gCode));
}

void RobotArm::saveCoordinates(Coordinate3D coordinates) {
    xPosition = coordinates.getX();
    yPosition = coordinates.getY();
    zPosition = coordinates.getZ();
}

void RobotArm::writeData(const char *command, unsigned int size) {
    connection.writeData(command, size);
    connection.writeData("\n", 1);
}

char* RobotArm::readData() {
    connection.readData(response, 1024);
    std::cout << "\n\n\n";
    std::cout << response << std::endl;
    std::cout << "\n\n\n";
    return response;
}

bool RobotArm::commandDone() {
    readData();
    for (int i = 0; i < sizeof(response); i++) {
        if (response[i] == 'o') {
            if (response[i+1] == 'k') {
                return true;
            }
        }
    }
    return false;
}

void RobotArm::saveSpeed(int _speed) {
    speed = _speed;
}

void RobotArm::createGCode(Coordinate3D coordinates, int speed) {
    std::string coordinatesAsTextX = std::to_string(coordinates.getX());
    std::string coordinatesAsTextY = std::to_string(coordinates.getY());
    std::string coordinatesAsTextZ = std::to_string(coordinates.getZ());
    std::string speedAsText = std::to_string(speed);

    strcpy(gCode, "G0 X");
    strcat(gCode, coordinatesAsTextX.c_str());
    strcat(gCode, " Y");
    strcat(gCode, coordinatesAsTextY.c_str());
    strcat(gCode, " Z");
    strcat(gCode, coordinatesAsTextZ.c_str());
    strcat(gCode, " F");
    strcat(gCode, speedAsText.c_str());
    strcat(gCode, "\n");
}