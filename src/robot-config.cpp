#include "robot-config.h"
#include "vex.h"

using namespace vex;
using namespace std;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);
motor LeftSideMotorA = motor(PORT16, ratio18_1, true);
motor LeftSideMotorB = motor(PORT17, ratio18_1, true);
motor LeftSideMotorC = motor(PORT20, ratio18_1, false);
// motor_group LeftSide = motor_group(LeftSideMotorA, LeftSideMotorB,
// LeftSideMotorC);
motor RightSideMotorA = motor(PORT7, ratio18_1, false);
motor RightSideMotorB = motor(PORT8, ratio18_1, false);
motor RightSideMotorC = motor(PORT9, ratio18_1, true);
// motor_group RightSide = motor_group(RightSideMotorA, RightSideMotorB,
// RightSideMotorC);
motor outtake1 = motor(PORT19, ratio36_1, false);
// motor outake2 = motor (PORT20,ratio36_1, true);
// motor_group Outtake = motor_group(outake1, outake2);
motor Intake = motor(PORT6, ratio18_1, false);
pneumatics OutakeYeet(Brain.ThreeWirePort.A);
pneumatics Expantion(Brain.ThreeWirePort.B);
inertial Inertial1 = inertial(PORT1);
rotation RotationR = rotation(PORT11, false);
rotation RotationL = rotation(PORT14, false);
rotation Rotation3 = rotation(PORT4, false);
distance DistanceBOI = distance(PORT5);
optical VisionBOI = optical(PORT3, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // nothing to initialize
}