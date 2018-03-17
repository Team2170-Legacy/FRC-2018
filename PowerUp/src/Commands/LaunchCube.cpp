/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "LaunchCube.h"
#include "../Robot.h"
#include "../Subsystems/Intake.h"

LaunchCube::LaunchCube() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::intake.get());
}

// Called just before this Command runs the first time
void LaunchCube::Initialize() {
	Robot::intake->OpenIntake();
	SetTimeout(2.0);
}

// Called repeatedly when this Command is scheduled to run
void LaunchCube::Execute() {
	if (TimeSinceInitialized() > 0.1) {
		Robot::intake->IntakeRev(intakeModeType::both, 1.0);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool LaunchCube::IsFinished() {
	return IsTimedOut();
}

// Called once after isFinished returns true
void LaunchCube::End() {
	Robot::intake->IntakeOff();
	Robot::intake->CloseIntake();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LaunchCube::Interrupted() {
	End();
}
