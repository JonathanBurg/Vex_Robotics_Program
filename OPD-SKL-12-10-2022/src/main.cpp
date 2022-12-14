/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Jonathan Burgener                                         */
/*                                                                            */
/*    Created:      Sat DEC 10 2022                                           */
/*    Description:  Skills Auton for the Spin Up comp                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "robot-config.h"
#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// functions for displaying temperatures of the motors and battery capacity
// to brain and controllers
int Output = 1;
int a = 80;
void sleep(int ms) { task::sleep(ms); }

// brain screen info

void brainGUI() {
  int RT = (RightSideMotorA.temperature(percent) +
            RightSideMotorB.temperature(percent) +
            RightSideMotorC.temperature(percent)) /
           3;
  int LT = (LeftSideMotorA.temperature(percent) +
            LeftSideMotorC.temperature(percent) +
            LeftSideMotorC.temperature(percent)) /
           3;
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("This is the batterys capacity in percent: ");
  Brain.Screen.print(Brain.Battery.capacity(percent));
  Brain.Screen.newLine();
  Brain.Screen.print("This is the right side's tempature: ");
  Brain.Screen.print(RT);
  Brain.Screen.newLine();
  Brain.Screen.print("This is the left side's tempature: ");
  Brain.Screen.print(LT);
  Brain.Screen.newLine();
  Brain.Screen.print("This is the Outtakes's tempature: ");
  Brain.Screen.print(outtake1.temperature(percent));
  Brain.Screen.newLine();
  Brain.Screen.print("This is the Intakes tempature: ");
  Brain.Screen.print(Intake.temperature(percent));
  Brain.Screen.newLine();
  if (Output == 1) {
    Brain.Screen.print("Long Range Mode Engaged");
  } else if (Output == 2) {
    Brain.Screen.print("Short Range Mode Engaged");
  } else if (Output == 3) {
    Brain.Screen.print("SUPER Long Range Mode Engaged");
  }
  Brain.Screen.newLine();
  Brain.Screen.print("Inertials Value: ");
  Brain.Screen.print(Inertial1.value());
  Brain.Screen.newLine();
  Brain.Screen.print("RightSide rotations: ");
  Brain.Screen.print(RotationR.position(turns));
  Brain.Screen.newLine();
  Brain.Screen.print("LeftSide Rotations: ");
  Brain.Screen.print(RotationL.position(turns));
  Brain.Screen.newLine();
  Brain.Screen.print("Outtake RPM: ");
  Brain.Screen.print(Rotation3.velocity(rpm));
  Brain.Screen.newLine();
  Brain.Screen.print("Distance from wall(in): ");
  Brain.Screen.print(DistanceBOI.objectDistance(inches));
  Brain.Screen.newLine();
  Brain.Screen.print("Detects a red object?: ");
  Brain.Screen.print(VisionBOI.hue());
  Brain.Screen.newLine();
}

// controller1
void controller1Screen() {
  int RT = (RightSideMotorA.temperature(percent) +
            RightSideMotorB.temperature(percent) +
            RightSideMotorC.temperature(percent)) /
           3;
  int LT = (LeftSideMotorA.temperature(percent) +
            LeftSideMotorC.temperature(percent) +
            LeftSideMotorC.temperature(percent)) /
           3;
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("BT %: "); // battery in percent
  Controller1.Screen.print(Brain.Battery.capacity(percent));
  Controller1.Screen.print("    OTT %: "); // outtake temp in %
  Controller1.Screen.print(outtake1.temperature());
  Controller1.Screen.newLine();
  Controller1.Screen.print("RS %: "); // right side temp in percent
  Controller1.Screen.print(RT);
  if (Output == 1) {
    Controller1.Screen.print("   | LRM");
  } else if (Output == 2) {
    Controller1.Screen.print("   | SRM");
  } else if (Output == 3) {
    Controller1.Screen.print("   | SLRM");
  }
  Controller1.Screen.newLine();
  Controller1.Screen.print("LS %: "); // left side temp in percent
  Controller1.Screen.print(LT);
  Controller1.Screen.print("RGB:", VisionBOI.hue());
}

int Rv = 100;
int Lv = 100;

void LeftSideFWD() {
  LeftSideMotorA.spin(fwd, Lv, pct);
  LeftSideMotorB.spin(fwd, Lv, pct);
  LeftSideMotorC.spin(fwd, Lv, pct);
}

void RightSideFWD() {
  RightSideMotorA.spin(fwd, Rv, pct);
  RightSideMotorB.spin(fwd, Rv, pct);
  RightSideMotorC.spin(fwd, Rv, pct);
}

void LeftSideREV() {
  LeftSideMotorA.spin(reverse, Lv, pct);
  LeftSideMotorB.spin(reverse, Lv, pct);
  LeftSideMotorC.spin(reverse, Lv, pct);
}

void RightSideREV() {
  RightSideMotorA.spin(reverse, Rv, pct);
  RightSideMotorB.spin(reverse, Rv, pct);
  RightSideMotorC.spin(reverse, Rv, pct);
}
void LeftSideSTP() {
  LeftSideMotorA.stop(hold);
  LeftSideMotorB.stop(hold);
  LeftSideMotorC.stop(hold);
}

void RightSideSTP() {
  RightSideMotorA.stop(hold);
  RightSideMotorB.stop(hold);
  RightSideMotorC.stop(hold);
}
void shoot() {
  OutakeYeet.open();
  sleep(5);
  OutakeYeet.close();
}
// these help with auton
// these do things such as driving the whole bot forward or left or whatever the
// name says. its a ton easier than typing more than neccessary
// 1 turn ~= 6-7"
void SidesFWD() {

  LeftSideFWD();
  RightSideFWD();
}

void SidesREV() {

  LeftSideREV();
  RightSideREV();
}

void SidesSTP() {
  RightSideSTP();
  LeftSideSTP();
}

void SidesRight() {
  LeftSideFWD();
  RightSideREV();
}

void SidesLeft() {
  RightSideFWD();
  LeftSideREV();
}

void SRM() {
  // control for our outake close range mode
  if (Controller1.ButtonDown.pressing()) {
    a = 70;
    Output = 2;
  }
}

void LRM() {
  // control for our outtake long range mode.
  if (Controller1.ButtonUp.pressing()) {
    a = 80;
    Output = 1;
  }
}

void SS() {
  if (Controller1.ButtonLeft.pressing()) {
    a = 100;
    Output = 3;
  }
}

void Outtake() {
  bool press = true;
  while (true) {
    if (Controller1.ButtonR2.pressing()) {
      press = true;
      outtake1.spin(fwd, a, pct);
    }

    if (Controller1.ButtonX.pressing()) {
      press = false;
      outtake1.stop(coast);
    }
  }
}

void Rumble() {
  while (true) {
    if (Rotation3.velocity(rpm) >= 2150) {

      Controller1.rumble("-.-");
    }
  }
}

void pre_auton(void) { vexcodeInit(); }

void autonomous(void) {
  while (true) {
    double distance = 0;
    RotationR.setPosition(0, turns);
    RotationL.setPosition(0, turns);
    Lv = 75;
    Rv = 75;
    outtake1.spin(fwd, 78, pct);

    SidesFWD();
    waitUntil(DistanceBOI.objectDistance(inches) <= 4);
    SidesSTP();

    RotationR.setPosition(0, turns);
    RotationL.setPosition(0, turns);
    sleep(100);

    Intake.spin(reverse, 100, pct);
    wait(.4, sec);
    Intake.stop(coast);

    SidesREV(); // Rotate first roller
    waitUntil(RotationR.position(turns) <= -0.4);
    SidesSTP();
    sleep(100);

    RotationR.setPosition(0, turns);
    RotationL.setPosition(0, turns);
    sleep(100);

    distance = -1.73; // turn around to face goal
    RightSideREV();
    waitUntil(RotationR.position(turns) <= distance);
    SidesSTP();

    if (RotationR.position(turns) < distance - 0.1) {
      Lv = 15;
      Rv = 15;
      LeftSideREV();
      waitUntil(RotationR.position(turns) == distance);
      SidesSTP();
    }

    if (RotationR.position(turns) > distance + 0.1) {
      Lv = 25;
      Rv = 25;
      RightSideREV();
      waitUntil(RotationR.position(turns) == distance);
      SidesSTP();
    }

    RotationR.setPosition(0, turns);
    RotationL.setPosition(0, turns);
    sleep(100);

    distance = 1.73;
    LeftSideFWD();
    waitUntil(RotationL.position(turns) >= distance);
    SidesSTP();

    if (RotationL.position(turns) > distance + .1) {
      Lv = 15;
      Rv = 15;
      RightSideFWD();
      waitUntil(RotationL.position(turns) == distance);
      SidesSTP();
    }

    if (RotationL.position(turns) < distance - .1) {
      Lv = 25;
      Rv = 25;
      LeftSideFWD();
      waitUntil(RotationL.position(turns) == distance);
      SidesSTP();
    }

    RotationR.setPosition(0, turns);
    RotationL.setPosition(0, turns);
    SidesSTP();

    waitUntil(Rotation3.velocity(rpm) >= 2250);

    // is looking at the goal at other end of field (working)
    OutakeYeet.open();
    wait(.25, sec);
    OutakeYeet.close();
    waitUntil(Rotation3.velocity(rpm) >= 2250);
    sleep(100);
    OutakeYeet.open();
    wait(.25, sec);
    OutakeYeet.close();
    wait(.5, sec);
    outtake1.stop(coast);

    RotationR.setPosition(0, turns);
    RotationL.setPosition(0, turns);
    sleep(100);

    distance = -1.73;
    LeftSideFWD();
    waitUntil(RotationL.position(turns) <= distance);
    SidesSTP();

    if (RotationL.position(turns) < distance - .1) {
      Lv = 15;
      Rv = 15;
      RightSideFWD();
      waitUntil(RotationL.position(turns) == distance);
      SidesSTP();
    }

    if (RotationL.position(turns) > distance + .1) {
      Lv = 25;
      Rv = 25;
      LeftSideFWD();
      waitUntil(RotationL.position(turns) == distance);
      SidesSTP();
    }

    RotationR.setPosition(0, turns);
    RotationL.setPosition(0, turns);
    sleep(100);
    
    /*
        Lv = 75;
        Rv = 75;

        RotationR.setPosition(0, turns);
        RotationL.setPosition(0, turns);
        sleep(100);
        // at this point the cylinder has been spun and we should be parallel
       with
        // the white lines (WORKING)

        SidesREV();
        waitUntil(RotationR.position(turns) <= -5.5);
        Lv = 60;
        Rv = 60;
        waitUntil(RotationR.position(turns) <= -6);
        Lv = 40;
        Rv = 40;
        waitUntil(RotationR.position(turns) <= -6.5);
        SidesSTP();

        if (RotationR.position(turns) < -6.6) {
          Lv = 25;
          Rv = 25;
          SidesREV();
          waitUntil(RotationR.position(turns) == -6.5);
          SidesSTP();
        }

        if (RotationR.position(turns) > -6.4) {
          Lv = 25;
          Rv = 25;
          SidesFWD();
          waitUntil(RotationR.position(turns) == -6.5);
          SidesSTP();
        }

        Lv = 75;
        Rv = 75;

        RotationR.setPosition(0, turns);
        RotationL.setPosition(0, turns);
        sleep(100);

        RightSideREV();
        waitUntil(RotationR.position(turns) <= -2.16);
        SidesSTP();

        if (RotationR.position(turns) < -2.26) {
          Lv = 25;
          Rv = 25;
          RightSideFWD();
          waitUntil(RotationR.position(turns) == -2.16);
          SidesSTP();
        }

        if (RotationR.position(turns) > -1.84) {
          Lv = 25;
          Rv = 25;
          RightSideREV();
          waitUntil(RotationR.position(turns) == -2.16);
          SidesSTP();
        }

        Lv = 75;
        Rv = 75;

        // parallel with line(WORKING)

        RotationR.setPosition(0, turns);
        RotationL.setPosition(0, turns);

        sleep(100);
        Rv = 45;
        Lv = 45;
        SidesFWD();
        waitUntil(RotationR.position(turns) >= .3);
        SidesSTP();
        Lv = 75;
        Rv = 75;

        waitUntil(Rotation3.velocity(rpm) >= 2250);

        // is looking at the goal at other end of field (WORKING)
        OutakeYeet.open();
        wait(.25, sec);
        OutakeYeet.close();
        waitUntil(Rotation3.velocity(rpm) >= 2250);
        sleep(100);
        OutakeYeet.open();
        wait(.25, sec);
        OutakeYeet.close();
        wait(.5, sec);
        outtake1.stop(coast);

        // has shot 2 disks into the top goal (WORKING)

        RotationR.setPosition(0, turns);
        RotationL.setPosition(0, turns);
        sleep(100);

        // Go back and turn left to line back up with line

        Rv = 45;
        Lv = 45;
        SidesREV();
        waitUntil(RotationR.position(turns) <= -.3);

        RotationR.setPosition(0, turns);
        RotationL.setPosition(0, turns);

        LeftSideFWD();
        waitUntil(RotationR.position(turns) >= 2.16);
        SidesSTP();

        RotationR.setPosition(0, turns);
        RotationL.setPosition(0, turns);
        sleep(100);
        // End of left side competition auton
        if (RotationL.position(turns) > 2.26) {
          Lv = 25;
          Rv = 25;
          LeftSideREV();
          waitUntil(RotationL.position(turns) == 2.16);
          SidesSTP();
        }

        if (RotationL.position(turns) < 1.84) {
          Lv = 25;
          Rv = 25;
          LeftSideFWD();
          waitUntil(RotationL.position(turns) == 2.16);
          SidesSTP();
        }

        RotationR.setPosition(0, turns);
        RotationL.setPosition(0, turns);

        Lv = 75;
        Rv = 75;
        /*
            SidesREV();
            waitUntil(RotationR.position(turns) <= -5.5);
            Lv = 60;
            Rv = 60;
            waitUntil(RotationR.position(turns) <= -6);
            Lv = 40;
            Rv = 40;
            waitUntil(RotationR.position(turns) <= -6.5);
            SidesSTP();

            if (RotationR.position(turns) < -6.6) {
              Lv = 25;
              Rv = 25;
              SidesREV();
              waitUntil(RotationR.position(turns) == -6.5);
              SidesSTP();
            }

            if (RotationR.position(turns) > -6.4) {
              Lv = 25;
              Rv = 25;
              SidesFWD();
              waitUntil(RotationR.position(turns) == -6.5);
              SidesSTP();
            }
            SidesSTP();
            sleep(100);

            RotationR.setPosition(0, turns);
            RotationL.setPosition(0, turns);

            Rv = 40;
            Lv = 40;
            RightSideREV();
            */
    RotationR.setPosition(0, turns);
    RotationL.setPosition(0, turns);

    break;
  }
}

void usercontrol(void) {
  RightSideMotorA.stop(coast);
  RightSideMotorB.stop(coast);
  RightSideMotorC.stop(coast);
  LeftSideMotorA.stop(coast);
  LeftSideMotorB.stop(coast);
  LeftSideMotorC.stop(coast);
  RotationR.setPosition(0, turns);
  RotationL.setPosition(0, turns);
  Lv = 100;
  Rv = 100;
  Brain.Timer.reset();
  while (true) {
    LeftSideMotorA.spin(forward, Controller1.Axis3.value(), pct);
    LeftSideMotorB.spin(forward, Controller1.Axis3.value(), pct);
    LeftSideMotorC.spin(forward, Controller1.Axis3.value(), pct);
    RightSideMotorA.spin(forward, Controller1.Axis2.value(), pct);
    RightSideMotorB.spin(forward, Controller1.Axis2.value(), pct);
    RightSideMotorC.spin(forward, Controller1.Axis2.value(), pct);

    // if(Brain.Timer.value() >= 95){

    if (Controller1.ButtonRight.pressing()) {
      Expantion.open();
      sleep(100);
      Expantion.close();
    }
    // }

    // The piston control so we can launch rings
    if (Controller1.ButtonR1.pressing()) {
      shoot(); // fire outtake piston
    }

    // intake control so we can eat up rings
    if (Controller1.ButtonL1.pressing()) {
      Intake.spin(fwd, 100, pct);
    } else if (Controller1.ButtonL2.pressing()) {
      Intake.spin(reverse, 100, pct);
    } // spins up intake
    else {
      Intake.stop();
    }
  }

  wait(10, msec); // Sleep the task for a short amount of time to
                  // prevent wasted resources.
}

void thred() {
  thread tusercontroll(usercontrol);
  thread tshoot(shoot);
  thread tSRM(SRM);
  thread tLRM(LRM);
  thread tSUS(SS);
  thread tOuttake(Outtake);
  thread tRumble(Rumble);
}

int main() {

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  Competition.drivercontrol(thred);
  while (true) {
    VisionBOI.setLight(ledState::on);
    // a forever loop to print the temperatures to the screens
    brainGUI();
    controller1Screen();
    // controller2Screen();
    SRM();
    LRM();
    SS();
    // TEST();
  }
  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(5, msec);
  }
}
