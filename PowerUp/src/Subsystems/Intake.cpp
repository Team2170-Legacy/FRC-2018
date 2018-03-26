// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.




#include "Intake.h"
#include "../RobotMap.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Intake::Intake() :
		frc::Subsystem("Intake"),
		kIntakeSpeed(Preferences::GetInstance()->GetDouble("IntakeSpeed", 0.6)),
		kOuttakeSpeed(Preferences::GetInstance()->GetDouble("OuttakeSpeed", -0.6)) {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    leftIntakeWheel = RobotMap::intakeLeftIntakeWheel;
    rightIntakeWheel = RobotMap::intakeRightIntakeWheel;
    intakeDoubleSolenoid = RobotMap::intakeIntakeDoubleSolenoid;
    compressor = RobotMap::intakeCompressor;
    lSLeft = RobotMap::intakeLSLeft;
    lSRight = RobotMap::intakeLSRight;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    climberDoubleSolenoid = RobotMap::climberDoubleSolenoid;
	compressor->Start();
	CloseIntake();
}

void Intake::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Intake::Periodic() {
    // Put code here to be run every loop

}

void Intake::OpenIntake() {
	intakeDoubleSolenoid->Set(DoubleSolenoid::Value::kForward);
}

void Intake::CloseIntake() {
	intakeDoubleSolenoid->Set(DoubleSolenoid::Value::kReverse);
}

bool Intake::IntakeIsClosed() {
	return (intakeDoubleSolenoid->Get() == DoubleSolenoid::Value::kReverse);
}

void Intake::IntakeFwd() {
	leftIntakeWheel->Set(-kIntakeSpeed);
	rightIntakeWheel->Set(kIntakeSpeed);
}

void Intake::IntakeRev() {
	leftIntakeWheel->Set(kOuttakeSpeed);
	rightIntakeWheel->Set(-kOuttakeSpeed);
}

void Intake::IntakeOff() {
	leftIntakeWheel->Set(0.0);
	rightIntakeWheel->Set(0.0);
}

bool Intake::getIntakeLSLeft() {
	return lSLeft->Get();
}

bool Intake::getIntakeLSRight() {
	return lSRight->Get();
}

void Intake::IntakeFwd(intakeModeType intakeMode, double speed) {
	if (intakeModeType::left || intakeModeType::both) {
		leftIntakeWheel->Set(-speed);
	}

	if (intakeModeType::right || intakeModeType::both) {
		rightIntakeWheel->Set(speed);
	}
}

void Intake::IntakeRev(intakeModeType intakeMode, double speed) {
	if (intakeMode == intakeModeType::left) {
			leftIntakeWheel->Set(speed);
	}

	else if (intakeMode == intakeModeType::right) {
			rightIntakeWheel->Set(-speed);
	}

	else {
			leftIntakeWheel->Set(speed);
			rightIntakeWheel->Set(-speed);
	}
}

void Intake::IntakeOff(intakeModeType intakeMode) {
	if (intakeModeType::left || intakeModeType::both) {
		leftIntakeWheel->Set(0.0);
	}
	if (intakeModeType::right || intakeModeType::both) {
		rightIntakeWheel->Set(0.0);
	}
}

void Intake::ClimberRaise() {
	climberDoubleSolenoid->Set(DoubleSolenoid::Value::kReverse);
}

void Intake::ClimberLower() {
	climberDoubleSolenoid->Set(DoubleSolenoid::Value::kForward);
}

void Intake::ClimberStop() {
	climberDoubleSolenoid->Set(DoubleSolenoid::Value::kOff);
}
