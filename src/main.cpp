/**
 * @file
 * @brief     The Robot Arm module for PC
 * @author    Jeroen van Hattem
 * @license   See LICENSE
 */
#include "robot_arm.hpp"
#include <iostream>

/*
- *     Te weinig code
- *     Sleep in constructor ipv main
- *     commandDone() --> Blocking / Non-blocking versies van move(), closeClaw(), etc.
- *     Check of hij klaar is met moven door de huidige coordinaten op te vragen en te vergelijken met de opgegeven coordinaten.
- *     Dubbele if in command done; mogelijkheid "ok" te missen als deze op de grens van 2 slices ligt
- *     readData via return value of niet?
- *     createGCode kan betere naam hebben: maakt enkel speciale gCodes, en levert niets op. Was beter geweest als deze private is
- *     Waarom creatGCode (of nog beter: move) niet hergebruiken voor de reset?
- *     Isoleren GCode code goed idee (want duidelijk wat aangepast moet worden voor andere arm) maar niet consequent gedaan
- *     Hergebruik je code: bijvoorbeeld, gebruik move in moveX (etc) - of vice versa
- *     Delta moves waren mooie toevoeging geweest: niet alleen move naar X = 42, maar ook move 3 over X-as (moveDeltaX)
- Tests missen compleet. Hardware tests zouden een goede toevoeging zijn.
- *     Meer code / functionaliteit: moveSafe (check boundaries), bounaries aanpassen (bijvoorbeeld om een pen vast te kunnen
houden), moveDeltaX/Y/Z, ... (wees creatief)
- *     moveDelta()
- *     moveSafe()
- *     Fix serial voor Windows (receiving too many lines)
*/

int main() {
    RobotArm uArm = RobotArm();
    // Coordinate3D coordinates = Coordinate3D(150, 0, 50);
    // // Coordinate3D coordinates2 = Coordinate3D(100, -180, 0);
    // int x, y, z;
    // int speed = 500000;
    // int rotation;

    uArm.rotateClaw(80);
    std::cout << "Rotation: " << uArm.getClawRotation() << std::endl;
    uArm.rotateClaw(70);
    std::cout << "Rotation: " << uArm.getClawRotation() << std::endl;
    uArm.rotateClaw(60);
    std::cout << "Rotation: " << uArm.getClawRotation() << std::endl;

    // Coordinate3D coordinates = Coordinate3D(150, 0, 50);
    // // Coordinate3D coordinates2 = Coordinate3D(100, -180, 0);
    // int x, y, z;
    // int speed = 500000;

    // std::cout << "Moving" << std::endl;
    // uArm.move(coordinates, speed);
    // while (!uArm.commandDone(1)) {
    // }

    // std::cout << "Closing claw" << std::endl;
    // uArm.closeClaw();

    // uArm.mSleep(2000);

    // std::cout << "Resetting position" << std::endl;
    // uArm.resetPosition();
    // while (!uArm.commandDone(1)) {
    // }

    // std::cout << "Opening claw" << std::endl;
    // uArm.openClaw();

    // uArm.mSleep(2000);

    return 0;
}
