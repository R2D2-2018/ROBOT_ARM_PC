/**
 * @file
 * @brief     Test file
 * @author    Jeroen van Hattem
 * @license   See LICENSE
 */
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "../src/coordinate3d.hpp"
#include "../src/serial.hpp"
#include "../src/robot_arm.hpp"
#include "catch.hpp"
#include <unistd.h> // Sleep function

RobotArm uArm = RobotArm();

// g++ test_main.cpp ../src/robot_arm.cpp ../src/serial.cpp ../src/coordinate3d.cpp -o test.exe

TEST_CASE("Wait for arm to reach destination") {
    Coordinate3D coordinates = Coordinate3D(150, -150, 100);
    int speed = 50000;
    uArm.move(coordinates, speed);    
    while(!uArm.commandDone(1));
    REQUIRE(uArm.getCurrentPosition() == uArm.getActualPosition());
}

// TEST_CASE("Actual coordinates check") {
//     Coordinate3D coordinates = Coordinate3D(150, -150, 100);
//     int speed = 50000;
//     uArm.move(coordinates, speed);   
//     sleep(5); 
//     uArm.commandDone(1);
// }

TEST_CASE("Claw state") {
    uArm.closeClaw();
    REQUIRE(uArm.clawState());

    uArm.openClaw();
    REQUIRE(!uArm.clawState());
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