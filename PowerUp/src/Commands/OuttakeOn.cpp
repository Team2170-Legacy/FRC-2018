/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OuttakeOn.h"

OuttakeOn::OuttakeOn(double timeout) : TimedCommand(timeout) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::intake.get());
}

// Called just before this Command runs the first time
void OuttakeOn::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void OuttakeOn::Execute() {
	Robot::intake->IntakeRev();
}

// Called once after command times out
void OuttakeOn::End() {
	Robot::intake->IntakeOff();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OuttakeOn::Interrupted() {
	End();
}
