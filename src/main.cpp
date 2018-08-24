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
    Coordinate3D coordinates = Coordinate3D(150, 150, 100);
    int speed = 50000;

    uArm.move(coordinates, speed);
    while (!uArm.commandDone(1)) {
    }

    if (uArm.getCurrentPosition() == uArm.getActualPosition()) {
        std::cout << "Waiting for moving succesfull" << std::endl;
    } else {
        std::cout << "Waiting for moving unsuccesfull" << std::endl;
    }

    coordinates = Coordinate3D(1000, 300, 100);
    if (!uArm.move(coordinates, speed)) {
        std::cout << "Safety Bouds succesfull" << std::endl;
    } else {
        std::cout << "Safety Bouds unsuccesfull" << std::endl;
    }

    uArm.moveX(200);
    while (!uArm.commandDone(1)) {
    }

    if (uArm.getCurrentPosition() == uArm.getActualPosition()) {
        std::cout << "X position succesfull" << std::endl;
    } else {
        std::cout << "X position unsuccesfull" << std::endl;
    }

    uArm.moveY(150);
    while (!uArm.commandDone(1)) {
    }

    if (uArm.getCurrentPosition() == uArm.getActualPosition()) {
        std::cout << "Y position succesfull" << std::endl;
    } else {
        std::cout << "Y position unsuccesfull" << std::endl;
    }

    uArm.moveZ(80);
    while (!uArm.commandDone(1)) {
    }

    if (uArm.getCurrentPosition() == uArm.getActualPosition()) {
        std::cout << "Z position succesfull" << std::endl;
    } else {
        std::cout << "Z position unsuccesfull" << std::endl;
    }

    // uArm.moveDeltaX(-10);
    // while (!uArm.commandDone(1)) {
    // }

    // if (uArm.getCurrentPosition() == uArm.getActualPosition()) {
    //     std::cout << "Delta X position succesfull" << std::endl;
    // } else {
    //     std::cout << "Delta X position unsuccesfull" << std::endl;
    // }

    // uArm.moveDeltaY(10);
    // while (!uArm.commandDone(1)) {
    // }

    // if (uArm.getCurrentPosition() == uArm.getActualPosition()) {
    //     std::cout << "Delta Y position succesfull" << std::endl;
    // } else {
    //     std::cout << "Delta Y position unsuccesfull" << std::endl;
    // }

    // uArm.moveDeltaZ(10);
    // while (!uArm.commandDone(1)) {
    // }

    // if (uArm.getCurrentPosition() == uArm.getActualPosition()) {
    //     std::cout << "Delta Z position succesfull" << std::endl;
    // } else {
    //     std::cout << "Delta Z position unsuccesfull" << std::endl;
    // }

    std::cout << "RESETTING" << std::endl;

    uArm.resetPosition();
    while (!uArm.commandDone(1)) {
    }

    if (uArm.getCurrentPosition() == uArm.getActualPosition()) {
        std::cout << "Position reset succesfull" << std::endl;
    } else {
        std::cout << "Position reset unsuccesfull" << std::endl;
    }

    uArm.rotateClaw(180);
    std::cout << "Claw rotation: " << uArm.getClawRotation() << std::endl;

    uArm.closeClaw();
    uArm.mSleep(2000);
    // std::cout << "Claw state: " << uArm.getClawState() << std::endl;

    uArm.openClaw();
    uArm.mSleep(2000);
    std::cout << "Claw state: " << uArm.getClawState() << std::endl;

    uArm.disablePump();
    uArm.mSleep(100);
    std::cout << "Pump state: " << uArm.pumpState() << std::endl;

    uArm.disablePump();
    uArm.mSleep(100);
    std::cout << "Pump state: " << uArm.pumpState() << std::endl;

    return 0;
}
