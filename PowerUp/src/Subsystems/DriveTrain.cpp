// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.




#include "DriveTrain.h"
#include "../RobotMap.h"
#include "../Commands/TeleopTankDrive.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

DriveTrain::DriveTrain() :
		frc::Subsystem("DriveTrain"), kOpenLoopRamp(
				Preferences::GetInstance()->GetDouble("Drivetrain Ramp", 0.0)), m_StickDeadband(
				Preferences::GetInstance()->GetDouble("Drive Deadband", 0.02)), MaxVelocity(
				Preferences::GetInstance()->GetDouble("Max Velocity", 825.0)), MagicAccel(
				Preferences::GetInstance()->GetDouble("Magic Accel", 1000)), mAxleTrack(
				Preferences::GetInstance()->GetDouble("Axle Track", 30.0)), mWheelSize(
				Preferences::GetInstance()->GetDouble("Wheel Size", 5.0)), mCntsPerRev(
				Preferences::GetInstance()->GetDouble("Drive Cnts Per Rev", 4096.0)){

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	talonSRXMasterLeft = RobotMap::driveTrainTalonSRXMasterLeft;
	talonSRXMasterRight = RobotMap::driveTrainTalonSRXMasterRight;
	differentialDrive1 = RobotMap::driveTrainDifferentialDrive1;
	talonSRXSlaveLeft1 = RobotMap::driveTrainTalonSRXSlaveLeft1;
	talonSRXSlaveLeft2 = RobotMap::driveTrainTalonSRXSlaveLeft2;
	talonSRXSlaveRight1 = RobotMap::driveTrainTalonSRXSlaveRight1;
	talonSRXSlaveRight2 = RobotMap::driveTrainTalonSRXSlaveRight2;
	powerDistributionPanel = RobotMap::driveTrainPowerDistributionPanel;

	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	differentialDrive1->SetSafetyEnabled(false);
	InitMotors();
	differentialDrive1->SetDeadband(m_StickDeadband);
}

void DriveTrain::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new TeleopTankDrive());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void DriveTrain::Periodic() {
    // Put code here to be run every loop

}

void DriveTrain::InitMotors() {
	//Initialize slave motors to follower mode
	talonSRXSlaveLeft1->Set(ControlMode::Follower, 4.0);
	talonSRXSlaveLeft2->Set(ControlMode::Follower, 4.0);
	talonSRXSlaveRight1->Set(ControlMode::Follower, 1.0);
	talonSRXSlaveRight2->Set(ControlMode::Follower, 1.0);


	talonSRXMasterLeft->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 0);
	talonSRXMasterRight->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 0);

	//Master motor direction configuration
	talonSRXMasterLeft->SetInverted(false);
	talonSRXMasterRight->SetInverted(false);
	talonSRXMasterLeft->SetSensorPhase(false);

	if (Preferences::GetInstance()->GetBoolean("Practice Bot", false)) {
		talonSRXMasterRight->SetSensorPhase(true);
	}
	else {
		talonSRXMasterRight->SetSensorPhase(false);
	}

	//Master left and master right set control modes
	talonSRXMasterLeft->Set(ControlMode::Velocity, 0.0);
	talonSRXMasterRight->Set(ControlMode::Velocity, 0.0);

	// Set open loop ramp rates
	talonSRXMasterLeft->ConfigOpenloopRamp(kOpenLoopRamp, 10);
	talonSRXMasterRight->ConfigOpenloopRamp(kOpenLoopRamp, 10);

	talonSRXMasterLeft->ConfigMotionAcceleration(MagicAccel, 10);
	talonSRXMasterRight->ConfigMotionAcceleration(MagicAccel, 10);
	talonSRXMasterLeft->ConfigMotionCruiseVelocity(MaxVelocity, 10);
	talonSRXMasterRight->ConfigMotionCruiseVelocity(MaxVelocity, 10);

	talonSRXMasterLeft->ChangeMotionControlFramePeriod(5);
	talonSRXMasterRight->ChangeMotionControlFramePeriod(5);
}

void DriveTrain::TankDrive(double leftSpeed, double rightSpeed) {


	if (!mReverseDrive) {
		differentialDrive1->TankDrive(leftSpeed, rightSpeed, true);
	} else {
		differentialDrive1->TankDrive(-rightSpeed, -leftSpeed, true);
	}
}

void DriveTrain::CurvatureDrive(double xSpeed, double zRotation, bool isQuickTurn){

//	differentialDrive1->CurvatureDrive(xSpeed, zRotation, isQuickTurn);
	differentialDrive1->CurvatureDrive(MapStick(xSpeed), MapStick(zRotation), isQuickTurn);
}

void DriveTrain::ArcadeDrive(double xSpeed, double zRotation, bool squaredInputs){

//	differentialDrive1->ArcadeDrive(xSpeed, zRotation,squaredInputs);
	differentialDrive1->ArcadeDrive(MapStick(xSpeed), MapStick(zRotation),squaredInputs);
}

void DriveTrain::TankDriveVelocity(double left, double right){
	if (!mReverseDrive) {
		talonSRXMasterLeft->Set(ControlMode::Velocity, left * MaxVelocity);
		talonSRXMasterRight->Set(ControlMode::Velocity, -right * MaxVelocity);
	} else {
		talonSRXMasterLeft->Set(ControlMode::Velocity, -left * MaxVelocity);
		talonSRXMasterRight->Set(ControlMode::Velocity,	right * MaxVelocity);
	}

}

void DriveTrain::FillProfileBuffer(
		std::shared_ptr<const ProfileData> LeftWheel) {
	size_t i;
	TrajectoryPoint pt;
	phoenix::ErrorCode error;

	pt.zeroPos = true;
	pt.isLastPoint = false;
	pt.profileSlotSelect0 = 0;

	talonSRXMasterRight->Set(ControlMode::MotionProfile, SetValueMotionProfile::Disable);
	talonSRXMasterRight->Set(ControlMode::MotionProfile, SetValueMotionProfile::Disable);
	talonSRXMasterLeft->ClearMotionProfileTrajectories();
	talonSRXMasterLeft->ClearMotionProfileHasUnderrun(0);
	talonSRXMasterRight->ClearMotionProfileTrajectories();
	talonSRXMasterRight->ClearMotionProfileHasUnderrun(0);

	for (i = 0; i < LeftWheel->size(); i++) {
		// check if this is the last point
		if ((i + 1) == LeftWheel->size()) {
			pt.isLastPoint = true;
		}

		pt.position = LeftWheel->at(i).at(0);
		pt.velocity = LeftWheel->at(i).at(1);
		pt.timeDur = TrajectoryDuration_20ms;
//		pt.timeDur = (TrajectoryDuration)LeftWheel->at(i).at(2);
		if ((error = talonSRXMasterLeft->PushMotionProfileTrajectory(pt))) {
			printf("left %d\n", error);
		}

		// Negative position and velocity for right side
		pt.position = -pt.position;
		pt.velocity = -pt.velocity;
		if ((error = talonSRXMasterRight->PushMotionProfileTrajectory(pt))) {
			printf("right %d\n", error);
		}
		pt.zeroPos = false;
	}
}

void DriveTrain::FillProfileBuffer(std::shared_ptr<const ProfileData> LeftWheel,
		std::shared_ptr<const ProfileData> RightWheel) {
	size_t i;
	TrajectoryPoint pt;

	pt.zeroPos = true;
	pt.isLastPoint = false;
	pt.profileSlotSelect0 = 0;

	talonSRXMasterRight->Set(ControlMode::MotionProfile, SetValueMotionProfile::Disable);
	talonSRXMasterRight->Set(ControlMode::MotionProfile, SetValueMotionProfile::Disable);
	talonSRXMasterRight->ClearMotionProfileTrajectories();
	talonSRXMasterRight->ClearMotionProfileHasUnderrun(0);
	talonSRXMasterRight->ClearMotionProfileTrajectories();
	talonSRXMasterRight->ClearMotionProfileHasUnderrun(0);

	for (i = 0; i < LeftWheel->size(); i++) {
		// check if this is the last point
		if ((i + 1) == LeftWheel->size()) {
			pt.isLastPoint = true;
		}

		pt.position = LeftWheel->at(i).at(0);
		pt.velocity = LeftWheel->at(i).at(1);
//		pt.timeDur = (TrajectoryDuration)LeftWheel->at(i).at(2);
		pt.timeDur = TrajectoryDuration_20ms;
		talonSRXMasterLeft->PushMotionProfileTrajectory(pt);

		// Use right wheel profile for right side
		pt.position = -RightWheel->at(i).at(0);
		pt.velocity = -RightWheel->at(i).at(1);
//		pt.timeDur = (TrajectoryDuration)RightWheel->at(i).at(2);
		pt.timeDur = TrajectoryDuration_20ms;
		talonSRXMasterRight->PushMotionProfileTrajectory(pt);
		pt.zeroPos = false;
	}
}

void DriveTrain::ServiceMotionProfile() {
	talonSRXMasterLeft->ProcessMotionProfileBuffer();
	talonSRXMasterRight->ProcessMotionProfileBuffer();
}

void DriveTrain::SetChassisMode(ControlMode mode) {
	switch (mode) {
	case ControlMode::MotionProfile:
		SetMotionProfileMode();
		break;
	case ControlMode::Position:
		SetClosedLoopMode();
		break;
	case ControlMode::Velocity:
		SetVelocityMode();
		break;
	case ControlMode::MotionMagic:
		SetMotionMagicMode();
		break;
	case ControlMode::PercentOutput:
	default:
		SetVoltagePercentMode();
		break;
	}
}

void DriveTrain::SetVelocityMode() {
	SetMotorGains(1, 0);
	talonSRXMasterLeft->Set(ControlMode::Velocity,0.0);
	talonSRXMasterRight->Set(ControlMode::Velocity,0.0);

}

void DriveTrain::SetClosedLoopMode() {
	talonSRXMasterLeft->Set(ControlMode::Position,0.0);
	talonSRXMasterRight->Set(ControlMode::Position,0.0);
}

void DriveTrain::SetMotionProfileMode() {
	SetMotorGains(0, 0);
	talonSRXMasterLeft->Set(ControlMode::MotionProfile, SetValueMotionProfile::Disable);
	talonSRXMasterLeft->ConfigMotionProfileTrajectoryPeriod(10, 0);
	talonSRXMasterLeft->SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, 10, 0);
	talonSRXMasterRight->Set(ControlMode::MotionProfile, SetValueMotionProfile::Disable);
	talonSRXMasterRight->ConfigMotionProfileTrajectoryPeriod(10, 0);
	talonSRXMasterRight->SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, 10, 0);
}

void DriveTrain::SetMotionMagicMode() {
	SetMotorGains(0, 0);
	talonSRXMasterLeft->Set(ControlMode::MotionMagic,
			talonSRXMasterLeft->GetSelectedSensorPosition(0));
	talonSRXMasterRight->Set(ControlMode::MotionMagic,
			talonSRXMasterRight->GetSelectedSensorPosition(0));
}

void DriveTrain::SetMotorGains(int idx, int pidIdx) {
	talonSRXMasterLeft->SelectProfileSlot(idx, pidIdx);
	talonSRXMasterRight->SelectProfileSlot(idx, pidIdx);
}

void DriveTrain::SetVoltagePercentMode(){
	talonSRXMasterLeft->Set(ControlMode::PercentOutput, 0.0);
	talonSRXMasterRight->Set(ControlMode::PercentOutput, 0.0);
}

void DriveTrain::ResetChassisYaw() {
//	if (gyro->IsConnected()) {
//		gyro->Reset();
//	}
}

void DriveTrain::SetMotionProfileState(SetValueMotionProfile mode) {
	if (talonSRXMasterLeft->GetControlMode()
			== ControlMode::MotionProfile) {
		talonSRXMasterLeft->Set(ControlMode::MotionProfile, mode);
	}
	if (talonSRXMasterRight->GetControlMode()
			== ControlMode::MotionProfile) {
		talonSRXMasterRight->Set(ControlMode::MotionProfile, mode);
	}
}
void DriveTrain::SetChassisWheelVelocity(double left, double right) {
	if ((talonSRXMasterLeft->GetControlMode()
			== ControlMode::Velocity)
			&& (talonSRXMasterRight->GetControlMode()
					== ControlMode::Velocity)) {
		talonSRXMasterLeft->Set(left);
		talonSRXMasterRight->Set(-right);
	}
}

bool DriveTrain::MotionProfileComplete() {
	bool Complete = false;
	MotionProfileStatus LeftStatus, RightStatus;

	talonSRXMasterLeft->GetMotionProfileStatus(LeftStatus);
	talonSRXMasterRight->GetMotionProfileStatus(RightStatus);

//	printf("Remaining top buffer points:  %d\n", LeftStatus.topBufferRem);
//	printf("Bottom buffer count:  %d\n", LeftStatus.btmBufferCnt);
//	printf("IsUnderrun status:  %d\n", LeftStatus.isUnderrun);

	// Start motion profile processing after 5 points are in talon buffer
	if ((!mMotionProcessingActive) && (LeftStatus.btmBufferCnt > 5)) {
		SetMotionProfileState(SetValueMotionProfile::Enable);
		printf("Enable motion profile\n");
		mMotionProcessingActive = true;
	}

	if ((LeftStatus.activePointValid && LeftStatus.isLast)
			&& (RightStatus.activePointValid
					&& RightStatus.isLast)) {
		Complete = true;
		mMotionProcessingActive = false;
		printf("Motion complete\n");
	}

	return Complete;
}

void DriveTrain::TankDriveWithTriggers(double Left, double Right, double Trigger) {
//	double newLeft = 0.0;
//	double newRight = 0.0;
//	double ProcessedLeft = Left;
//	double ProcessedRight = Right;
//	double fExponent = 1.0;
//
//	ProcessedLeft = DEADBAND(AxisPower(ProcessedLeft, fExponent), 0.07);
//
//	ProcessedRight = DEADBAND(AxisPower(ProcessedRight, fExponent), 0.07);
//
//	ProcessedLeft = MapStick(ProcessedLeft);
//	ProcessedRight = MapStick(ProcessedRight);
//
//	newLeft = fmax(fmin(ProcessedLeft + (Trigger * .8), 1.0), -1.0);
//	newRight = fmax(fmin(ProcessedRight + (Trigger * .8), 1.0), -1.0);
//
//	// Select velocity mode or throttle mode
//	if (kDriveVelocityMode) {
//		SetChassisMode(ControlMode::Velocity);
//	} else {
//		SetChassisMode(ControlMode::PercentOutput);
//	}
//
//	// Determine if we are using gyro corrected straight movement
//	if ((ProcessedLeft == 0.0) && (ProcessedRight == 0.0)) {
//		if (DEADBAND(Trigger, 0.10) == 0.0) {
//			ResetChassisYaw();
//			bDriveStraight = true;
//		}
//	} else {
//		bDriveStraight = false;
//	}
//
//	if (bDriveStraight) {
//		if (kDriveVelocityMode) {
//			Trigger *= kDriveMaxVelocity;
//
//		}
//		DriveStraight(Trigger * 0.8f);
//	} else {
//		if (kDriveVelocityMode) {
//			newLeft *= kDriveMaxVelocity;
//			newRight *= kDriveMaxVelocity;
//
//		}
//		if (!mReverseDrive) {
//			robotDrive->TankDrive(newLeft, newRight, false);
//		} else {
//			robotDrive->TankDrive(-newRight, -newLeft, false);
//		}
//	}
	//cANTalonSlaveRight->Set(2);
	//cANTalonSlaveLeft->Set(1);
}

void DriveTrain::DriveStraight(bool Backwards) {
//	if (Backwards) {
//		DriveStraight(-mAutoVelocity);
//	} else {
//		DriveStraight(mAutoVelocity);
//	}
}

void DriveTrain::DriveStraight(double magnitude) {

//	//double ChassisAngle = ReadChassisYaw();
//	double ChassisAngle = 0.0;
//	double kYawGain = 0.0;
//
//
//	if (mReverseDrive) {
//		magnitude = -magnitude;
//	}
//	if (magnitude > 0.0) {
//		robotDrive->Drive(magnitude, kYawGain * ChassisAngle);
//	} else {
//		robotDrive->Drive(magnitude, -kYawGain * ChassisAngle);
//	}
}

void DriveTrain::SetVelocity(double velocity) {

	talonSRXMasterLeft->Set(ControlMode::Velocity,velocity);
	talonSRXMasterRight->Set(ControlMode::Velocity,-velocity);

}

void DriveTrain::ArcadeDriveVelocity(double xSpeed, double zRotation,
                                    bool squaredInputs) {

	xSpeed = Limit(xSpeed);
	xSpeed = ApplyDeadband(xSpeed, m_StickDeadband);

	zRotation = Limit(zRotation);
	zRotation = ApplyDeadband(zRotation, m_StickDeadband);

  // Square the inputs (while preserving the sign) to increase fine control
  // while permitting full power.
  if (squaredInputs) {
    xSpeed = std::copysign(xSpeed * xSpeed, xSpeed);
    zRotation = std::copysign(zRotation * zRotation, zRotation);
  }

  double leftMotorOutput;
  double rightMotorOutput;

  double maxInput =
      std::copysign(std::max(std::abs(xSpeed), std::abs(zRotation)), xSpeed);

  if (xSpeed >= 0.0) {
    // First quadrant, else second quadrant
    if (zRotation >= 0.0) {
      leftMotorOutput = maxInput;
      rightMotorOutput = xSpeed - zRotation;
    } else {
      leftMotorOutput = xSpeed + zRotation;
      rightMotorOutput = maxInput;
    }
  } else {
    // Third quadrant, else fourth quadrant
    if (zRotation >= 0.0) {
      leftMotorOutput = xSpeed + zRotation;
      rightMotorOutput = maxInput;
    } else {
      leftMotorOutput = maxInput;
      rightMotorOutput = xSpeed - zRotation;
    }
  }

  talonSRXMasterLeft->Set(ControlMode::Velocity, leftMotorOutput * MaxVelocity);
  talonSRXMasterRight->Set(ControlMode::Velocity, -rightMotorOutput * MaxVelocity);
}

double DriveTrain::Limit(double value) {

  if (value > 1.0) {
    return 1.0;
  }

  if (value < -1.0) {
    return -1.0;
  }
  return value;
}



/**
 * Returns 0.0 if the given value is within the specified range around zero. The
 * remaining range between the deadband and 1.0 is scaled from 0.0 to 1.0.
 *
 * @param value    value to clip
 * @param deadband range around zero
 */
double DriveTrain::ApplyDeadband(double value, double deadband) {
  if (std::abs(value) > deadband) {
    if (value > 0.0) {
      return (value - deadband) / (1.0 - deadband);
    }
    else {
      return (value + deadband) / (1.0 - deadband);
    }
  }
  else {
    return 0.0;
  }
}

/**
 * Curvature drive method for differential drive platform.
 *
 * The rotation argument controls the curvature of the robot's path rather than
 * its rate of heading change. This makes the robot more controllable at high
 * speeds. Also handles the robot's quick turn functionality - "quick turn"
 * overrides constant-curvature turning for turn-in-place maneuvers.
 *
 * @param xSpeed      The robot's speed along the X axis [-1.0..1.0]. Forward is
 *                    positive.
 * @param zRotation   The robot's rotation rate around the Z axis [-1.0..1.0].
 *                    Clockwise is positive.
 * @param isQuickTurn If set, overrides constant-curvature turning for
 *                    turn-in-place maneuvers.
 */
void DriveTrain::CurvatureDriveVelocity(double xSpeed, double zRotation,
                                       bool isQuickTurn) {
  xSpeed = Limit(xSpeed);
  xSpeed = ApplyDeadband(xSpeed, m_StickDeadband);

  zRotation = Limit(zRotation);
  zRotation = ApplyDeadband(zRotation, m_StickDeadband);

  double angularPower;
  bool overPower;

  if (isQuickTurn) {
    if (std::abs(xSpeed) < m_quickStopThreshold) {
      m_quickStopAccumulator = (1 - m_quickStopAlpha) * m_quickStopAccumulator +
                               m_quickStopAlpha * Limit(zRotation) * 2;
    }
    overPower = true;
    angularPower = zRotation;
  } else {
    overPower = false;
    angularPower = std::abs(xSpeed) * zRotation - m_quickStopAccumulator;

    if (m_quickStopAccumulator > 1) {
      m_quickStopAccumulator -= 1;
    } else if (m_quickStopAccumulator < -1) {
      m_quickStopAccumulator += 1;
    } else {
      m_quickStopAccumulator = 0.0;
    }
  }

  double leftMotorOutput = xSpeed + angularPower;
  double rightMotorOutput = xSpeed - angularPower;

  // If rotation is overpowered, reduce both outputs to within acceptable range
  if (overPower) {
    if (leftMotorOutput > 1.0) {
      rightMotorOutput -= leftMotorOutput - 1.0;
      leftMotorOutput = 1.0;
    } else if (rightMotorOutput > 1.0) {
      leftMotorOutput -= rightMotorOutput - 1.0;
      rightMotorOutput = 1.0;
    } else if (leftMotorOutput < -1.0) {
      rightMotorOutput -= leftMotorOutput + 1.0;
      leftMotorOutput = -1.0;
    } else if (rightMotorOutput < -1.0) {
      leftMotorOutput -= rightMotorOutput + 1.0;
      rightMotorOutput = -1.0;
    }
  }

  // Normalize the wheel speeds
  double maxMagnitude =
      std::max(std::abs(leftMotorOutput), std::abs(rightMotorOutput));
  if (maxMagnitude > 1.0) {
    leftMotorOutput /= maxMagnitude;
    rightMotorOutput /= maxMagnitude;
  }

  talonSRXMasterLeft->Set(ControlMode::Velocity, leftMotorOutput * MaxVelocity);
  talonSRXMasterRight->Set(ControlMode::Velocity, -rightMotorOutput * MaxVelocity);

}



double DriveTrain::MapStick(double stick) {
	double NewStick = fabs(stick);

	if (NewStick < kStickBreak) {
		NewStick = (NewStick / kStickBreak) * kThrottleBreak;
	} else {
		NewStick = kThrottleBreak
				+ ((1 - NewStick) / (1 - kStickBreak)) * (1 - kThrottleBreak);
	}

	if (stick < 0.0) {
		NewStick = -NewStick;
	}

	return NewStick;
}

