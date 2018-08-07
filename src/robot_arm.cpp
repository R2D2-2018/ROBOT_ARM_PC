/**
 * @file
 * @brief     This file contains the Robot Arm library
 * @author    Jeroen van Hattem
 * @license   See LICENSE
 */
#include "robot_arm.hpp"

RobotArm::RobotArm() {
    strcopy(gCode, "P2202\n"); // Send a command to ensure the connection is working. This should return the hardware version.
    writeData(gCode, sizeof(gCode));
}

void RobotArm::move(Coordinate3D coordinates, int speed) {
    createGCode(coordinates, speed);
    saveCoordinates(coordinates);
    saveSpeed(speed);
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
    strcopy(gCode, "G0 X150 Y0 Z0 F50000\n");
    writeData(gCode, sizeof(gCode));
}

void RobotArm::closeClaw() {
    strcopy(gCode, "M2232 V1\n");
    writeData(gCode, sizeof(gCode));
}

void RobotArm::openClaw() {
    strcopy(gCode, "M2232 V0\n");
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
    char coordinatesAsTextX[4];
    char coordinatesAsTextY[4];
    char coordinatesAsTextZ[4];
    char speedAsText[7];

    intToChar(coordinates.getX(), coordinatesAsTextX);
    intToChar(coordinates.getY(), coordinatesAsTextY);
    intToChar(coordinates.getZ(), coordinatesAsTextZ);
    intToChar(speed, speedAsText);

    strcopy(gCode, "G0 X");
    stradd(gCode, coordinatesAsTextX);
    stradd(gCode, " Y");
    stradd(gCode, coordinatesAsTextY);
    stradd(gCode, " Z");
    stradd(gCode, coordinatesAsTextZ);
    stradd(gCode, " F");
    stradd(gCode, speedAsText);
    stradd(gCode, "\n");
}

char *RobotArm::stradd(char *dest, const char *src) {
    char i, j;
    for (i = 0; dest[i] != '\0'; i++) {
    }
    for (j = 0; src[j] != '\0'; j++) {
        dest[i + j] = src[j];
    }
    dest[i + j] = '\0';
    return dest;
}

char *RobotArm::strcopy(char *dest, const char *src) {
    char *saved = dest;
    while (*src) {
        *dest++ = *src++;
    }
    *dest++ = '\0';
    *dest = 0;
    return saved;
}

char *RobotArm::intToChar(int number, char *dest) {
    if (number / 10 == 0) {
        *dest++ = number + '0';
        *dest = '\0';
        return dest;
    }

    dest = intToChar(number / 10, dest);
    *dest++ = number % 10 + '0';
    *dest = '\0';
    return dest;
}