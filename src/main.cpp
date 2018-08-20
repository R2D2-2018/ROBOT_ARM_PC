/**
 * @file
 * @brief     The Robot Arm module for PC
 * @author    Jeroen van Hattem
 * @license   See LICENSE
 */
#include <iostream>
#include "robot_arm.hpp"
#include "serial.hpp"


/*
- Te weinig code
- *     Sleep in constructor ipv main
- commandDone() --> Blocking / Non-blocking versies van move(), closeClaw(), etc.
- Check of hij klaar is met moven door de huidige coordinaten op te vragen en te vergelijken met de opgegeven coordinaten.
- *     Dubbele if in command done; mogelijkheid "ok" te missen als deze op de grens van 2 slices ligt
- *     readData via return value of niet?
- *     createGCode kan betere naam hebben: maakt enkel speciale gCodes, en levert niets op. Was beter geweest als deze private is
- *     Waarom creatGCode (of nog beter: move) niet hergebruiken voor de reset?
- *     Isoleren GCode code goed idee (want duidelijk wat aangepast moet worden voor andere arm) maar niet consequent gedaan
- *     Hergebruik je code: bijvoorbeeld, gebruik move in moveX (etc) - of vice versa
- *     Delta moves waren mooie toevoeging geweest: niet alleen move naar X = 42, maar ook move 3 over X-as (moveDeltaX)
- Tests missen compleet. Hardware tests zouden een goede toevoeging zijn.
- *     Meer code / functionaliteit: moveSafe (check boundaries), bounaries aanpassen (bijvoorbeeld om een pen vast te kunnen houden), moveDeltaX/Y/Z, ... (wees creatief)
- *     moveDelta()
- *     moveSafe()
- * 
- FIX SERIAL WINDOWS (receiving too many lines)

*/
#define DATA_LENGTH 255

int main() {
    RobotArm uArm = RobotArm();
    
    Coordinate3D coordinates = Coordinate3D(150, -150, 100);
    Coordinate3D coordinates2 = Coordinate3D(100, -180, 0);
    int x, y, z;
    int speed = 500000;

    // while (true) {
    //     std::cout << "Insert values\n";
    //     std::cin >> x;
    //     std::cin >> y;
    //     std::cin >> z;
        
    //     coordinates = Coordinate3D(x, y, z); 
    //     uArm.move(coordinates, speed);
    //     std::cout << "Command done: " << uArm.commandDone() << std::endl;
    // }

    // const char * P2220 = "P2220\n";

    // uArm.writeData(P2220, sizeof(P2220));
    // uArm.readData();

    std::cout << "Moving first time" << std::endl;

    uArm.move(coordinates, speed);
    while(!uArm.commandDone(1));

    std::cout << "Moving second time" << std::endl;

    uArm.move(coordinates2, speed);
    while(!uArm.commandDone(1));

    std::cout << "Done moving" << std::endl;
    

    // uArm.writeData(P2220, sizeof(P2220));
    // // uArm.readData();

    // uArm.writeData(P2220, sizeof(P2220));
    // uArm.readData();


    // uArm.getActualPosition();

    // std::cout << "Moving" << std::endl;
    // uArm.move(coordinates, speed);
    // while(uArm.commandDone() == 0);

    // std::cout << "Closing claw" << std::endl;
    // uArm.closeClaw();
    // while(uArm.commandDone() == 0);

    // sleep(2);

    // std::cout << "Resetting position" << std::endl;
    // uArm.resetPosition();
    // while(uArm.commandDone() == 0);

    // std::cout << "Opening claw" << std::endl;
    // uArm.openClaw();
    // while(uArm.commandDone() == 0);

    return 0;
}
