/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "IntakeOn.h"
#include "../Robot.h"

IntakeOn::IntakeOn() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::intake.get());
}

IntakeOn::IntakeOn(bool Enable) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::intake.get());
	mEnable = Enable;
}

// Called once when the command executes
void IntakeOn::Initialize() {
	if (mEnable) {
		Robot::intake->IntakeFwd();
	}
	else {
		Robot::intake->IntakeOff();
	}
}
