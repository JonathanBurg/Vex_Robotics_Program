#include "v5.h"
#include "v5_vcs.h"

using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern controller Controller2;
extern motor LeftSideMotorA;
extern motor LeftSideMotorB;
extern motor LeftSideMotorC;
extern motor RightSideMotorA;
extern motor RightSideMotorB;
extern motor RightSideMotorC;
extern motor Strafe;
// extern motor_group Outtake;
extern motor outtake1;
extern pneumatics OutakeYeet;
extern pneumatics Expantion;
extern motor Intake;
extern inertial Inertial1;
extern rotation RotationR;
extern rotation RotationL;
extern rotation Rotation3;
extern optical VisionBOI;
extern distance DistanceBOI;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);