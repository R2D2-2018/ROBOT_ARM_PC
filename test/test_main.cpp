/**
 * @file
 * @brief     Test file
 * @author    Jeroen van Hattem
 * @license   See LICENSE
 */
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "../src/coordinate3d.hpp"
#include "../src/robot_arm.hpp"
#include "../src/serial.hpp"
#include "catch.hpp"
#include <unistd.h> // Sleep function

RobotArm uArm = RobotArm();
int speed = 50000;

// g++ test_main.cpp ../src/robot_arm.cpp ../src/serial.cpp ../src/coordinate3d.cpp -o test.exe

TEST_CASE("Wait for arm to reach destination") {
    Coordinate3D coordinates = Coordinate3D(150, -150, 50);
    uArm.move(coordinates, speed);
    while (!uArm.commandDone(1)) {
    }

    REQUIRE(uArm.getCurrentPosition() == uArm.getActualPosition());
}

TEST_CASE("Safety bounds") {
    Coordinate3D coordinates = Coordinate3D(1000, 300, 100);

    REQUIRE(!uArm.move(coordinates, speed));
}

TEST_CASE("Move X") {
    uArm.moveX(200);
    while (!uArm.commandDone(1)) {
    }

    REQUIRE(uArm.getCurrentPosition() == uArm.getActualPosition());
}

TEST_CASE("Move Y") {
    uArm.moveY(150);
    while (!uArm.commandDone(1)) {
    }

    REQUIRE(uArm.getCurrentPosition() == uArm.getActualPosition());
}

TEST_CASE("Move Z") {
    uArm.moveZ(80);
    while (!uArm.commandDone(1)) {
    }

    REQUIRE(uArm.getCurrentPosition() == uArm.getActualPosition());
}

TEST_CASE("Move delta X") {
    uArm.moveDeltaX(10);
    while (!uArm.commandDone(1)) {
    }

    REQUIRE(uArm.getCurrentPosition() == uArm.getActualPosition());
}

TEST_CASE("Move delta Y") {
    uArm.moveDeltaY(10);
    while (!uArm.commandDone(1)) {
    }

    REQUIRE(uArm.getCurrentPosition() == uArm.getActualPosition());
}

TEST_CASE("Move delta Z") {
    uArm.moveDeltaZ(10);
    while (!uArm.commandDone(1)) {
    }

    REQUIRE(uArm.getCurrentPosition() == uArm.getActualPosition());
}

TEST_CASE("Reset position") {
    uArm.resetPosition();
    while (!uArm.commandDone(1)) {
    }

    REQUIRE(uArm.commandDone(1));
}

TEST_CASE("Rotate claw") {
    uArm.rotateClaw(180);

    REQUIRE(uArm.getClawRotation() == 180);
}

TEST_CASE("Close claw") {
    uArm.closeClaw();
    uArm.mSleep(2000);

    REQUIRE(uArm.getClawState());
}

TEST_CASE("Open claw") {
    uArm.openClaw();
    uArm.mSleep(2000);

    REQUIRE(!uArm.getClawState());
}

TEST_CASE("Enable pump") {
    uArm.disablePump();
    uArm.mSleep(2000);

    REQUIRE(uArm.pumpState());
}

TEST_CASE("Disable pump") {
    uArm.disablePump();
    uArm.mSleep(2000);

    REQUIRE(!uArm.pumpState());
}

TEST_CASE("Coordinates 3D get coordinates positive") {
    Coordinate3D coordinates(140, 150, 130);

    REQUIRE(coordinates.getX() == 140);
    REQUIRE(coordinates.getY() == 150);
    REQUIRE(coordinates.getZ() == 130);
}

TEST_CASE("Coordinates 3D get coordinates negative") {
    Coordinate3D coordinates(-140, -150, -130);

    REQUIRE(coordinates.getX() == -140);
    REQUIRE(coordinates.getY() == -150);
    REQUIRE(coordinates.getZ() == -130);
}

TEST_CASE("Coordinates 3D set coordinates positive") {
    Coordinate3D coordinates;
    coordinates.setX(140);
    coordinates.setY(150);
    coordinates.setZ(130);

    REQUIRE(coordinates.getX() == 140);
    REQUIRE(coordinates.getY() == 150);
    REQUIRE(coordinates.getZ() == 130);
}

TEST_CASE("Coordinates 3D set coordinates negative") {
    Coordinate3D coordinates;
    coordinates.setX(-140);
    coordinates.setY(-150);
    coordinates.setZ(-130);

    REQUIRE(coordinates.getX() == -140);
    REQUIRE(coordinates.getY() == -150);
    REQUIRE(coordinates.getZ() == -130);
}