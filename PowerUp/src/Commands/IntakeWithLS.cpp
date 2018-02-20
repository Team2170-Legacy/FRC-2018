/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "IntakeWithLS.h"
#include "../Subsystems/Intake.h"

IntakeWithLS::IntakeWithLS() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::intake.get());
}

// Called just before this Command runs the first time
void IntakeWithLS::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void IntakeWithLS::Execute() {
	bool lsL = Robot::intake->getIntakeLSLeft();
	bool lsR = Robot::intake->getIntakeLSRight();

	if (!lsL && !lsR)
		Robot::intake->IntakeFwd(intakeModeType::both, 0.6);
	else if (!lsL && lsR)
		Robot::intake->IntakeFwd(intakeModeType::left, 0.6);
	else if (lsL && !lsR)
		Robot::intake->IntakeFwd(intakeModeType::right, 0.6);
	else
		Robot::intake->IntakeOff(intakeModeType::both);
}

// Make this return true when this Command no longer needs to run execute()
bool IntakeWithLS::IsFinished() {
	bool lsL = Robot::intake->getIntakeLSLeft();
	bool lsR = Robot::intake->getIntakeLSRight();

	return lsL && lsR;
}

// Called once after isFinished returns true
void IntakeWithLS::End() {
	Robot::intake->IntakeOff();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IntakeWithLS::Interrupted() {

}
