/**
 * @file
 * @brief     Test file
 * @author    Jeroen van Hattem
 * @license   MIT
 */
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "../src/coordinate3d.hpp"
#include "../src/robot_arm.hpp"

#include "catch.hpp"

RobotArm uarmSwiftPro;
char text[100];

TEST_CASE("Append char* with another char*") {
    uarmSwiftPro.stradd(text, "how are you?");

    REQUIRE(text == "Hi, how are you?");
}

TEST_CASE("Copy char* to another char *") {
    uarmSwiftPro.strcopy(text, "Hi, ");

    REQUIRE(text == "Hi, ");
}

TEST_CASE("Convert integer to char *") {
    int x = 100;
    char buffer[5];

    uarmSwiftPro.intToChar(x, buffer);

    REQUIRE(buffer == "100");
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