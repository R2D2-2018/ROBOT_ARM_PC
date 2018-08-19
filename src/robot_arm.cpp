/**
 * @file
 * @brief     This file contains the Robot Arm library
 * @author    Jeroen van Hattem
 * @license   See LICENSE
 */
#include "robot_arm.hpp"

RobotArm::RobotArm() {
    sleep(2); // Wait until the serial connection is set up and the uArm responds.
    // strcpy(gCode, "P2202\n"); // Send a command to ensure the connection is working. This should return the hardware version.
    // writeData(gCode, sizeof(gCode));
    readData();
    writeData("\n\n", 2);
}

void RobotArm::move(Coordinate3D coordinates, int speed) {
    if (isSafeToMove(coordinates)) {
        if ((yPosition < 0 && coordinates.getY() > 0) || (yPosition > 0 && coordinates.getY() < 0)) {
            resetPosition(); // You can't go from one to the other side directly, so we move the arm back to the center first.
        }
        saveCoordinates(coordinates);
        saveSpeed(speed);
        moving = true;
        getMoveCode(coordinates, speed);
        std::cout << gCode << std::endl;
        writeData(gCode, sizeof(gCode));
    } else {
        std::cout << "Not safe to move there" << std::endl;
    }
}

void RobotArm::moveX(int value) {
    xPosition = value;
    Coordinate3D coordinates = Coordinate3D(value, yPosition, zPosition);
    move(coordinates, speed);
}

void RobotArm::moveY(int value) {
    yPosition = value;
    Coordinate3D coordinates = Coordinate3D(xPosition, value, zPosition);
    move(coordinates, speed);
}

void RobotArm::moveZ(int value) {
    zPosition = value;
    Coordinate3D coordinates = Coordinate3D(xPosition, yPosition, value);
    move(coordinates, speed);
}

void RobotArm::moveDeltaX(int value) {
    xPosition = xPosition + value;
    Coordinate3D coordinates = Coordinate3D(xPosition, yPosition, zPosition);
    move(coordinates, speed);
}

void RobotArm::moveDeltaY(int value) {
    yPosition = yPosition + value;
    Coordinate3D coordinates = Coordinate3D(xPosition, yPosition, zPosition);
    move(coordinates, speed);
}

void RobotArm::moveDeltaZ(int value) {
    zPosition = zPosition + value;
    Coordinate3D coordinates = Coordinate3D(xPosition, yPosition, zPosition);
    move(coordinates, speed);
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
    std::cout << response << std::endl;
    return response;
}

Coordinate3D RobotArm::getActualCoordinates() {
    char response[1024];
    std::string value;
    int i = 0;
    int x, y, z;

    strcpy(gCode, "P2220\n");
    writeData(gCode, sizeof(gCode));
    strcpy(response, readData());
    
    while (response[i] != '\0') {
        if (response[i] == 'X') {
            for (int j = 1; j <= 3; j++) {
                if(response[i+j] != '.') {
                    value.push_back(response[i+j]);
                }
            }
            x = std::stoi(value);
            std::cout << "X VALUE: " << x << std::endl;
            value.clear();
        }

        else if (response[i] == 'Y') {
            for (int j = 1; j <= 3; j++) {
                if(response[i+j] != '.') {
                    value.push_back(response[i+j]);
                }
            }
            y = std::stoi(value);
            std::cout << "Y VALUE: " << x << std::endl;
            value.clear();
        }

        else if (response[i] == 'Z') {
            for (int j = 1; j <= 3; j++) {
                if(response[i+j] != '.') {
                    value.push_back(response[i+j]);
                }
            }
            z = std::stoi(value);
            std::cout << "Z VALUE: " << x << std::endl;
            value.clear();
        }
        
        i++;
    }

    std::cout << "Actual coordinates: " << response << "\n";
}

bool RobotArm::isSafeToMove(Coordinate3D coordinates) {
    int x = coordinates.getX();
    int y = coordinates.getY();
    int z = coordinates.getZ();

    if (x <= -355 || x >= 355 || y <= -355 || y >= 355) {
        return false;
    }

    if ((y >= -80 && y <= 80) && x <= 350) {
        return true;
    } else if ((y >= -100 && y <= 100) && x <= 345) {
        return true;
    } else if ((y >= -120 && y <= 120) && x <= 338) {
        return true;
    } else if ((y >= -140 && y <= 140) && x <= 335) {
        return true;
    } else if ((y >= -160 && y <= 160) && x <= 325) {
        return true;
    } else if ((y >= -180 && y <= 180) && x <= 310) {
        return true;
    } else if ((y >= -200 && y <= 200) && x <= 295) {
        return true;
    } else if ((y >= -220 && y <= 220) && x <= 280) {
        return true;
    } else if ((y >= -240 && y <= 240) && x <= 265) {
        return true;
    } else if ((y >= -260 && y <= 260) && x <= 245) {
        return true;
    } else if ((y >= -280 && y <= 280) && x <= 225) {
        return true;
    } else if ((y >= -300 && y <= 300) && x <= 195) {
        return true;
    } else if ((y >= -320 && y <= 320) && x <= 155) {
        return true;
    } else if ((y >= -330 && y <= 330) && x <= 140) {
        return true;
    } else if ((y >= -340 && y <= 340) && x <= 115) {
        return true;
    } else if ((y >= -350 && y <= 350) && x <= 80) {
        return true;
    } else if ((y >= -355 && y <= 355) && x >= 0) {
        return true;
    }

    std::cout << "Not gonna work" << std::endl;

    return  false;
}

int RobotArm::commandDone() {
    readData();
    for (int i = 0; i < sizeof(response); i++) {
        if ((response[i] == 'o') && (response[i+1] == 'k')) {
            return 1;
        }
    }
    if (moving == true) {
        return 2;
    }
    return 0;
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
    strcat(gCode, ".00 Y");
    strcat(gCode, coordinatesAsTextY.c_str());
    strcat(gCode, ".00 Z");
    strcat(gCode, coordinatesAsTextZ.c_str());
    strcat(gCode, ".00 F");
    strcat(gCode, speedAsText.c_str());
    strcat(gCode, "\n");
}