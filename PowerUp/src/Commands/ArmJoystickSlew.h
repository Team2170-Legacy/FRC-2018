/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Command.h>

#define DEADBAND(val, limit)	((fabs(val) < limit) ? 0.0 : val)
#include "../Robot.h"

class ArmJoystickSlew : public frc::Command {
private:
	bool motorStopped = false;
public:
	ArmJoystickSlew();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};


