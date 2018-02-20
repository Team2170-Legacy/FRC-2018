/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ArmJoystickSlew.h"
#include <iostream>

ArmJoystickSlew::ArmJoystickSlew() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::arm.get());
}

// Called just before this Command runs the first time
void ArmJoystickSlew::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void ArmJoystickSlew::Execute() {
	double yChannel = -Robot::oi->getJoystickOperator()->GetY();
	std::cout << "Joystick Y: " << yChannel << std::endl;
	if ((fabs(yChannel) < 0.07)) {
		if (!motorStopped) {
			Robot::arm->SlewArmHold();
		}
		motorStopped = true;
	}
	else {
		Robot::arm->SlewArm(yChannel);
		motorStopped = false;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ArmJoystickSlew::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ArmJoystickSlew::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArmJoystickSlew::Interrupted() {

}
