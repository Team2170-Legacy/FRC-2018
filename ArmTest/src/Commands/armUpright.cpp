// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "armUpright.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

armUpright::armUpright(): frc::Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void armUpright::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void armUpright::Execute() {
	bool armLimitSwitchFrontValue = Robot::arm->readLimitSwitchFront();
	bool armLimitSwitchBackValue = Robot::arm->readLimitSwitchBack();

	int kArmSpeed = 100;							// Verify and possibly change this value
	int middleCount = 0;

	if (armLimitSwitchFrontValue == 1 || armLimitSwitchBackValue == 1) {
			Robot::arm->stopArmMotor();
	}

	else {
			// if arm is forward of center arm axis, move arm backwards until centered
			int encoderCounts = Robot::arm->readArmEncoder();

			if (encoderCounts < middleCount) {
				// move arm backwards until centered
				while (encoderCounts != middleCount) {
					Robot::arm->setArmMotorSpeed(kArmSpeed);
				}
				Robot::arm->stopArmMotor();
			}
			else if (encoderCounts > middleCount){
				while (encoderCounts != middleCount) {
					Robot::arm->setArmMotorSpeed(-kArmSpeed);
				}
				Robot::arm->stopArmMotor();
			}

			// if arm is backward of center arm axis, move arm forwards until centered
	}
}

// Make this return true when this Command no longer needs to run execute()
bool armUpright::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void armUpright::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void armUpright::Interrupted() {

}
