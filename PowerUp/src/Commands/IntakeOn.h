/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "Commands/InstantCommand.h"

class IntakeOn : public frc::InstantCommand {
public:
	IntakeOn();
	IntakeOn(bool Enable);
	void Initialize() override;
private:
	bool mEnable = false;
};

