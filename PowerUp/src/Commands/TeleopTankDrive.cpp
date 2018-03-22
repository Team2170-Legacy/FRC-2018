// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "TeleopTankDrive.h"


TeleopTankDrive::TeleopTankDrive(): frc::Command(),
driveMode(Preferences::GetInstance()->GetInt("Drive Mode", tankDrive)), driverXbox(0){
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::driveTrain.get());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	ThrottleInput.reset(new FilteredInput());
	ThrottleFilter.reset(new LinearDigitalFilter(
			LinearDigitalFilter::MovingAverage(ThrottleInput, 6)));
}

// Called just before this Command runs the first time
void TeleopTankDrive::Initialize() {
	if (driveMode == velocityMode) {
		Robot::driveTrain->SetChassisMode(ControlMode::Velocity);
	}
	else {
		Robot::driveTrain->SetChassisMode(ControlMode::PercentOutput);
	}

}

// Called repeatedly when this Command is scheduled to run
void TeleopTankDrive::Execute() {
	double Velocity = 0;
	double Arc = 0;

	switch (driveMode) {
	case tankDrive:
		Robot::driveTrain->TankDrive(
				-Robot::oi->getJoystickDriverLeft()->GetY(),
				-Robot::oi->getJoystickDriverRight()->GetY());
		break;
	case arcadeDrive:
		Velocity = -driverXbox.GetTriggerAxis(
				frc::GenericHID::JoystickHand::kLeftHand)
				+ driverXbox.GetTriggerAxis(
						frc::GenericHID::JoystickHand::kRightHand);
		Velocity = -driverXbox.GetY(frc::GenericHID::JoystickHand::kLeftHand);
		Arc = driverXbox.GetX(frc::GenericHID::JoystickHand::kRightHand);
		if (Velocity < 0.0) {
			Arc = -Arc;
		}
		if (Robot::driveTrain->isReverseDrive()) {
			Robot::driveTrain->CurvatureDrive(-Velocity, Arc,
					driverXbox.GetBumper(
							frc::GenericHID::JoystickHand::kRightHand));
		}
		else {
			Robot::driveTrain->CurvatureDrive(Velocity, Arc,
					driverXbox.GetBumper(
							frc::GenericHID::JoystickHand::kRightHand));
		}
		break;
	case curvatureDrive:
		Robot::driveTrain->CurvatureDrive(
				-driverXbox.GetY(frc::GenericHID::JoystickHand::kLeftHand),
				driverXbox.GetX(frc::GenericHID::JoystickHand::kLeftHand),
				driverXbox.GetBumper(
						frc::GenericHID::JoystickHand::kRightHand));
		break;
	case xboxTankDrive:
		Robot::driveTrain->TankDrive(
				-driverXbox.GetY(frc::GenericHID::JoystickHand::kLeftHand),
				-driverXbox.GetY(frc::GenericHID::JoystickHand::kRightHand));
		break;
	case velocityMode:
		Velocity = -driverXbox.GetTriggerAxis(
				frc::GenericHID::JoystickHand::kLeftHand)
				+ driverXbox.GetTriggerAxis(
						frc::GenericHID::JoystickHand::kRightHand);
		Velocity = -driverXbox.GetY(frc::GenericHID::JoystickHand::kLeftHand);

		// Filter velocity (throttle) input
		ThrottleInput->Update(Velocity);
		Velocity = ThrottleFilter->PIDGet();

		Arc = driverXbox.GetX(frc::GenericHID::JoystickHand::kRightHand);
		if (Velocity < 0.0) {
			Arc = -Arc;
		}
		if (Robot::driveTrain->isReverseDrive()) {
			Robot::driveTrain->CurvatureDriveVelocity(-Velocity, Arc,
					driverXbox.GetBumper(
							frc::GenericHID::JoystickHand::kRightHand));
		}
		else {
			Robot::driveTrain->CurvatureDriveVelocity(Velocity, Arc,
					driverXbox.GetBumper(
							frc::GenericHID::JoystickHand::kRightHand));
		}
		break;
	default:
		break;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool TeleopTankDrive::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void TeleopTankDrive::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TeleopTankDrive::Interrupted() {

}
