/**
 * @file
 * @brief     This file contains the Robot Arm library
 * @author    Jeroen van Hattem
 * @license   See LICENSE
 */
#include "robot_arm.hpp"

RobotArm::RobotArm() {
    mSleep(2000); // Wait until the serial connection is set up and the uArm responds.
    readData();
    writeData("\n\n", 2);
    currentPosition = getActualPosition();
}

bool RobotArm::move(Coordinate3D coordinates, int speed) {
    if (isSafeToMove(coordinates)) {
        if ((currentPosition.getY() < 0 && coordinates.getY() > 0) || (currentPosition.getY() > 0 && coordinates.getY() < 0)) {
            resetPosition(); // You can't go from one to the other side directly, so we move the arm back to the center first.
        }
        saveCoordinates(coordinates);
        saveSpeed(speed);
        getMoveCode(coordinates, speed);
        writeData(gCode, sizeof(gCode));
        return true;
    }
    return false;
}

bool RobotArm::rotateClaw(int value) {
    if (value >= 0 && value <= 180) {
        clawRotation = value;
        std::string rotation = std::to_string(value);
        strcpy(gCode, "G2202 N3 V");
        strcat(gCode, rotation.c_str());
        strcat(gCode, "\n");
        std::cout << gCode << std::endl;
        writeData(gCode, sizeof(gCode));
        mSleep(300);
        writeData(gCode, sizeof(gCode)); // Send twice intentionally, sometimes the claw doesn't reach the other side completely.
        writeData("\n", 1);
        return true;
    }
    return false;
}

void RobotArm::moveX(int value) {
    currentPosition.setX(value);
    Coordinate3D coordinates = Coordinate3D(value, currentPosition.getY(), currentPosition.getZ());
    move(coordinates, speed);
}

void RobotArm::moveY(int value) {
    currentPosition.setY(value);
    Coordinate3D coordinates = Coordinate3D(currentPosition.getX(), value, currentPosition.getZ());
    move(coordinates, speed);
}

void RobotArm::moveZ(int value) {
    currentPosition.setZ(value);
    Coordinate3D coordinates = Coordinate3D(currentPosition.getX(), currentPosition.getY(), value);
    move(coordinates, speed);
}

void RobotArm::moveDeltaX(int value) {
    currentPosition.setX(currentPosition.getX() + value);
    Coordinate3D coordinates = Coordinate3D(currentPosition.getX(), currentPosition.getY(), currentPosition.getZ());
    move(coordinates, speed);
}

void RobotArm::moveDeltaY(int value) {
    currentPosition.setY(currentPosition.getY() + value);
    Coordinate3D coordinates = Coordinate3D(currentPosition.getX(), currentPosition.getY(), currentPosition.getZ());
    move(coordinates, speed);
}

void RobotArm::moveDeltaZ(int value) {
    currentPosition.setZ(currentPosition.getZ() + value);
    Coordinate3D coordinates = Coordinate3D(currentPosition.getX(), currentPosition.getY(), currentPosition.getZ());
    move(coordinates, speed);
}

void RobotArm::resetClaw() {
    openClaw();
    rotateClaw(90);
}

void RobotArm::resetPosition() {
    Coordinate3D coordinates = Coordinate3D(150, 0, 0);
    move(coordinates, 50000);
}

void RobotArm::closeClaw() {
    strcpy(gCode, "M2232 V1\n");
    writeData(gCode, sizeof(gCode));
}

void RobotArm::openClaw() {
    strcpy(gCode, "M2232 V0\n");
    writeData(gCode, sizeof(gCode));
}

void RobotArm::enablePump() {
    strcpy(gCode, "M2231 V1\n");
    writeData(gCode, sizeof(gCode));
}

void RobotArm::disablePump() {
    strcpy(gCode, "M2231 V0\n");
    writeData(gCode, sizeof(gCode));
}

void RobotArm::saveCoordinates(Coordinate3D coordinates) {
    currentPosition = coordinates;
}

void RobotArm::writeData(const char *command, unsigned int size) {
    connection.writeData(command, size);
    connection.writeData("\n", 1);
}

char *RobotArm::getResponse() {
    return response;
}

char *RobotArm::readData() {
    connection.readData(response, 1024);
    return response;
}

int RobotArm::getClawRotation() {
    char response[1024];
    int i = 0;
    int rotation = 0;
    std::string value;

    strcpy(gCode, "P2206 N3\n");
    writeData(gCode, sizeof(gCode));
    std::cout << gCode << std::endl;
    strcpy(response, readData());
    std::cout << "RESPONSE: " << response << std::endl;

    while (response[i] != '\0') {
        if (response[i] == 'V') {
            for (unsigned int j = 1; j <= 5; j++) {
                if (response[i + j] != '.') {
                    std::cout << response[i + j];
                    value.push_back(response[i + j]);
                }
            }
            rotation = std::stoi(value);
            value.clear();
        }
        i++;
    }
    return rotation;
}

Coordinate3D RobotArm::getCurrentPosition() {
    return currentPosition;
}

Coordinate3D RobotArm::getActualPosition() {
    char response[30];
    std::string value;
    int i = 0;
    int x = 0;
    int y = 0;
    int z = 0;

    strcpy(gCode, "P2220\n");
    writeData(gCode, sizeof(gCode));
    strcpy(response, readData());
    strcpy(response, readData());

    while (response[i] != '\0') {
        if (response[i] == 'X') {
            for (unsigned int j = 1; j <= 4; j++) {
                if (response[i + j] != '.') {
                    value.push_back(response[i + j]);
                }
            }
            x = std::stoi(value);
            value.clear();
        } else if (response[i] == 'Y') {
            for (unsigned int j = 1; j <= 4; j++) {
                if (response[i + j] != '.') {
                    value.push_back(response[i + j]);
                }
            }
            y = std::stoi(value);
            value.clear();
        } else if (response[i] == 'Z') {
            for (unsigned int j = 1; j <= 4; j++) {
                if (response[i + j] != '.') {
                    value.push_back(response[i + j]);
                } else {
                    break;
                }
            }
            z = std::stoi(value);
            value.clear();
        }
        i++;
    }

    Coordinate3D actualCoordinates(x, y, z);
    return actualCoordinates;
}

bool RobotArm::getClawState() {
    char response[6];
    int clawState = 0;
    int i = 0;
    std::string value;

    strcpy(gCode, "P2232\n");
    writeData(gCode, sizeof(gCode));
    strcpy(response, readData());

    while (response[i] != '\0') {
        if (response[i] == 'V') {
            value.push_back(response[i + 1]);
            clawState = std::stoi(value);
            value.clear();
        }
        i++;
    }

    if (clawState == 1) {
        return true;
    } else {
        return false;
    }
}

bool RobotArm::pumpState() {
    char response[6];
    int pumpState = 0;
    int i = 0;
    std::string value;

    strcpy(gCode, "P2231\n");
    writeData(gCode, sizeof(gCode));
    strcpy(response, readData());

    while (response[i] != '\0') {
        if (response[i] == 'V') {
            value.push_back(response[i + 1]);
            pumpState = std::stoi(value);
            value.clear();
        }
        i++;
    }

    if (pumpState == 1) {
        return true;
    } else {
        return false;
    }
}

bool RobotArm::isSafeToMove(Coordinate3D coordinates) {
    int x = coordinates.getX();
    int y = coordinates.getY();
    int z = coordinates.getZ();

    if (x < 0 || x > 355 || y < -355 || y > 355 || z < 0 || z > 170) {
        return false;
    }

    if ((x >= 0 && x <= 160) && z <= 150) {
        return true;
    }

    if ((y >= -60 && y <= 60) && x <= 355 && z <= 90) {
        return true;
    } else if ((y >= -80 && y <= 80) && x <= 350 && z <= 100) {
        return true;
    } else if ((y >= -100 && y <= 100) && x <= 345 && z <= 110) {
        return true;
    } else if ((y >= -120 && y <= 120) && x <= 338 && z <= 120) {
        return true;
    } else if ((y >= -140 && y <= 140) && x <= 335 && z <= 125) {
        return true;
    } else if ((y >= -160 && y <= 160) && x <= 325 && z <= 135) {
        return true;
    } else if ((y >= -180 && y <= 180) && x <= 310 && z <= 145) {
        return true;
    } else if ((y >= -200 && y <= 200) && x <= 295 && z <= 155) {
        return true;
    } else if ((y >= -220 && y <= 220) && x <= 280 && z <= 160) {
        return true;
    } else if ((y >= -240 && y <= 240) && x <= 265 && z <= 165) {
        return true;
    } else if ((y >= -260 && y <= 260) && x <= 245 && z <= 170) {
        return true;
    } else if ((y >= -280 && y <= 280) && x <= 225 && z <= 170) {
        return true;
    } else if ((y >= -300 && y <= 300) && x <= 195 && z <= 170) {
        return true;
    } else if ((y >= -320 && y <= 320) && x <= 155 && z <= 150) {
        return true;
    } else if ((y >= -330 && y <= 330) && x <= 140 && z <= 140) {
        return true;
    } else if ((y >= -340 && y <= 340) && x <= 115 && z <= 55) {
        return true;
    } else if ((y >= -350 && y <= 350) && x <= 80 && z >= 50) {
        return true;
    } else if ((y >= -355 && y <= 355) && x >= 0 && z >= 50) {
        return true;
    }

    return false;
}

bool RobotArm::commandDone(int state) {
    readData();

    if (state == 0) { // "ok" command
        for (unsigned int i = 0; i < sizeof(response); i++) {
            if ((response[i] == 'o') && (response[i + 1] == 'k')) {
                return true;
            }
        }
        return false;
    }

    else if (state == 1) { // Moving
        if (currentPosition == getActualPosition()) {
            return true;
        }
        return false;
    }

    return false;
}

void RobotArm::saveSpeed(int _speed) {
    speed = _speed;
}

void RobotArm::getMoveCode(Coordinate3D coordinates, int speed) {
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

void RobotArm::mSleep(int milliseconds) {
#ifdef __WIN32__
    Sleep(milliseconds);
#else
    usleep(static_cast<useconds_t>(milliseconds) * 1000); // or use nanosleep on platforms where it's needed
#endif
}