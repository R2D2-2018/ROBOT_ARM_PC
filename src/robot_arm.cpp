/**
 * @file
 * @brief     This file contains the Robot Arm library
 * @author    Jeroen van Hattem
 * @license   See LICENSE
 */
#include "robot_arm.hpp"

RobotArm::RobotArm() {
    
}

void RobotArm::move(Coordinate3D coordinates, int speed) {
    createGCode(coordinates, speed);
    saveCoordinates(coordinates);
    saveSpeed(speed);
    connection.writeData(gCode, 255);
    readData();
}

void RobotArm::moveX(int value) {
    xPosition = value;
    Coordinate3D coordinates = Coordinate3D(value, yPosition, zPosition);
    createGCode(coordinates, speed);
    connection.writeData(gCode, 255);
    readData();
}

void RobotArm::moveY(int value) {
    yPosition = value;
    Coordinate3D coordinates = Coordinate3D(xPosition, value, zPosition);
    createGCode(coordinates, speed);
    connection.writeData(gCode, 255);
    readData();
}

void RobotArm::moveZ(int value) {
    zPosition = value;
    Coordinate3D coordinates = Coordinate3D(xPosition, yPosition, value);
    createGCode(coordinates, speed);
    connection.writeData(gCode, 255);
    readData();
}

void RobotArm::closeClaw() {
    connection.writeData("M2232 V1\n", 255);
}

void RobotArm::openClaw() {
    connection.writeData("M2232 V0\n", 255);
}

char* RobotArm::readData() {
    connection.readData(response, 100);
    // std::cout << response << std::endl;
    return response;
}

void RobotArm::saveCoordinates(Coordinate3D coordinates) {
    xPosition = coordinates.getX();
    yPosition = coordinates.getY();
    zPosition = coordinates.getZ();
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