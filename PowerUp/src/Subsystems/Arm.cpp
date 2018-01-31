// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.




#include "Arm.h"
#include "../RobotMap.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Arm::Arm() : frc::Subsystem("Arm") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    limitSwitchFront = RobotMap::armLimitSwitchFront;
    limitSwitchBack = RobotMap::armLimitSwitchBack;
    opticalFlagSensor = RobotMap::armOpticalFlagSensor;
    talonSRXArmMotor = RobotMap::armTalonSRXArmMotor;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}

void Arm::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Arm::Periodic() {
    // Put code here to be run every loop

}


// Put methods for controlling this subsystem
// here. Call these from Commands.

bool Arm::readLimitSwitchFront() {
	return !limitSwitchFront->Get();
	// Inversed due to Digital Output voltage pull-up (5V)
}

bool Arm::readLimitSwitchBack() {
	return !limitSwitchBack->Get();
	// Inversed due to Digital Output voltage pull-up (5V)
}

int Arm::readArmEncoder() {
	int pidIndex = 0;
	talonSRXArmMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::Analog, pidIndex, 0);
	return talonSRXArmMotor->GetSelectedSensorPosition(pidIndex);
	// *** Check this!!! ***
}

bool Arm::readArmOpticalFlagSensor() {
	return opticalFlagSensor->Get();
}

void Arm::stopArmMotor() {
	talonSRXArmMotor->StopMotor();
}

double Arm::getArmPosition() {
	int encoderCounts = readArmEncoder();
	int kEncoder90Deg = 76725;
	double angleDeg = (encoderCounts/kEncoder90Deg)*90;
	return angleDeg * DEG;
}

void Arm::setArmMotorSpeed(double speed) {
	talonSRXArmMotor->Set(speed);
}

void Arm::resetArmEncoder() {
	int pidIndex = 0;
	int resetValue = 0;
	talonSRXArmMotor->SetSelectedSensorPosition(resetValue, pidIndex, 0);
	//talonSRXArmMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::Analog, pidIndex, 0);
}

