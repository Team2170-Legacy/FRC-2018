/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ClimbUpWhileHeld.h"

ClimbUpWhileHeld::ClimbUpWhileHeld() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::intake.get());
}

// Called just before this Command runs the first time
void ClimbUpWhileHeld::Initialize() {
	Robot::intake->ClimbUp();
}

// Called repeatedly when this Command is scheduled to run
void ClimbUpWhileHeld::Execute() {
	Robot::intake->ClimbUp();
}

// Make this return true when this Command no longer needs to run execute()
bool ClimbUpWhileHeld::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ClimbUpWhileHeld::End() {
	Robot::intake->ClimbStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimbUpWhileHeld::Interrupted() {
	End();
}
