/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ArmSetPosition.h"

ArmSetPosition::ArmSetPosition(double positionRad) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::arm.get());
	armTargetPosition = positionRad;
}

ArmSetPosition::ArmSetPosition(int positionDeg) {
	Requires(Robot::arm.get());
	armTargetPosition = positionDeg * DEG;
}

// Called just before this Command runs the first time
void ArmSetPosition::Initialize() {
	Robot::arm->setArmTargetPosition(armTargetPosition);
	SetTimeout(2.0);
}

// Called repeatedly when this Command is scheduled to run
void ArmSetPosition::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool ArmSetPosition::IsFinished() {
	return (Robot::arm->isAtPosition() || IsTimedOut());
}

// Called once after isFinished returns true
void ArmSetPosition::End() {
	Robot::arm->SlewArmHold();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArmSetPosition::Interrupted() {
	Robot::arm->SlewArmHold();
}
