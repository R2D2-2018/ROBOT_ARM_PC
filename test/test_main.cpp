/**
 * @file
 * @brief     Test file
 * @author    Jeroen van Hattem
 * @license   See LICENSE
 */
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "../src/coordinate3d.hpp"
#include "../src/robot_arm.hpp"

#include "catch.hpp"

RobotArm uArm = RobotArm();

TEST_CASE("Actual coordinates check") {
    uArm.move()
    uArm.commandDone(1);
}

TEST_CASE("Claw state") {
    uArm.closeClaw();
    sleep(1);
    REQUIRE(uArm.clawState());

    uArm.openClaw();
    sleep(1);
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