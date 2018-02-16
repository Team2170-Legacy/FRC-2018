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
#include <iostream>
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

// Globals
static double lastFPGATime = 0.0;
//frc::Timer m_timer;

Arm::Arm() : frc::Subsystem("Arm"),
		kSlewSpeed((Preferences::GetInstance()->GetDouble("Arm Speed", 90.0)
				/ 180.0 * M_PI / 50.0)),
				kP_w(Preferences::GetInstance()->GetDouble("Arm kP Omega", 8.0)),
				wMax(Preferences::GetInstance()->GetDouble("Arm Omega Nax", 5.0)){
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    limitSwitchFront = RobotMap::armLimitSwitchFront;
    limitSwitchBack = RobotMap::armLimitSwitchBack;
    opticalFlagSensor = RobotMap::armOpticalFlagSensor;
    talonSRXArmMotor = RobotMap::armTalonSRXArmMotor;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	talonSRXArmMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 0);
	talonSRXArmMotor->SetSensorPhase(true);
	resetArmEncoder();
	mArmTargetPosition = getArmPosition();
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
	double kEncoder90Deg = ENCODER_COUNTS_PER_REV / 4;			// real value on 2018
	//double kEncoder90Deg = 5000.0;				// test value
	double angleDeg = (encoderCounts/kEncoder90Deg) * 90;
	//double angleDeg = encoderCounts;		//test
	return angleDeg * DEG;							// [radians]
}

void Arm::setArmMotorSpeed(double speed) {
	talonSRXArmMotor->Set(ControlMode::PercentOutput, speed);
}

void Arm::resetArmEncoder() {
	int pidIndex = 0;
	int resetValue = 0;
	talonSRXArmMotor->SetSelectedSensorPosition(resetValue, pidIndex, 0);
	//talonSRXArmMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::Analog, pidIndex, 0);
}

double Arm::getArmMotorTemp() {
	return talonSRXArmMotor->GetTemperature();
}

double Arm::setArmPosition(double alphaDesiredRad) {
	// Put CAN TALON in position mode
	//int armEncoder = readArmEncoder();
	//talonSRXArmMotor->Set(ControlMode::Position, armEncoder);

	// Perform calculations
	frc::Timer m_timer;
	lastFPGATime = m_timer.GetFPGATimestamp();


	double currentAlpha = getArmPosition();						// [radians]
	double e_alpha = alphaDesiredRad - currentAlpha; 			// [radians]
	double w = kP_w * e_alpha;									// [rad/sec]
	if (w > wMax) {
		w = wMax;
	}
	else if (w < -wMax){
		w = -wMax;
	}

	double currentFPGA = m_timer.GetFPGATimestamp();
	double elapsedTime = currentFPGA - lastFPGATime;
	lastFPGATime = currentFPGA;

	double alphaDesired_CAN_TALON = currentAlpha + (w * Ts);		// [radians]
	// Using actual elapsed time instead of Ts since our experiment shows that sample time is 4000 Hz
	//double alphaDesired_CAN_TALON = currentAlpha + (w * elapsedTime);		// [radians]

	//std::string Debug = alphaDesiredRad + "\t" + currentAlpha + "\t" + w + "\t" + alphaDesired_CAN_TALON;
	std::printf("Debug: %7.3f\t %7.3f\t %7.3f\t %7.3f\t %7.3f\n", alphaDesiredRad, currentAlpha, e_alpha, w, alphaDesired_CAN_TALON);
//	std::cout << (int)(alphaDesiredRad * 100) / 100.0 <<
//			"\t" << (int)(currentAlpha * 100) / 100.0 <<
//			"\t" << (int)(w * 100)/ 100.0 <<
//			"\t" << (int)(alphaDesired_CAN_TALON * 100) / 100.0 << std::endl;

	// Now have CAN TALON go to that position
	//double calculatedPosition = alphaDesired_CAN_TALON

	// Code below side steps our velocity control and lets the CAN Talon control position
	//double alphaDesired_CAN_TALON = alphaDesiredRad;				// [radians]

	// native units for encoder angle are: counts (??)
	double alphaDesired_CAN_TALON_native = alphaDesired_CAN_TALON / (2*PI) * ENCODER_COUNTS_PER_REV;
	//std::cout << alphaDesired_CAN_TALON_native << std::endl;

	//std::cout << "Elapsed Time: " << elapsedTime << std::endl;

	talonSRXArmMotor->Set(ControlMode::Position, alphaDesired_CAN_TALON_native);
	return currentAlpha;
}

double Arm::encoderCountsToDeg(int encoderCounts) {
	return (encoderCounts / ENCODER_COUNTS_PER_REV) * ROTATION_DEG;
}

double Arm::degToEncoderCounts(double degrees) {
	return (degrees / ROTATION_DEG) * ENCODER_COUNTS_PER_REV;
}
double Arm::RadSecToNativeUnits(double radSec) {
	// From calculations, 1 native unit is 0.043633 rad/sec, which is 22.918 native units per rad/sec
	return radSec * 22.918433;
}

double Arm::getArmMotorVelocity() {
//	int encoderCount = readArmEncoder();
//	frc::Timer m_timer;
//	while (m_timer.Get() < 0.01) {
//		// wait
//	}
	return talonSRXArmMotor->GetSelectedSensorVelocity(0);			// [
//	double radSec = 0;
//	if (m_timer.HasPeriodPassed(0.01)) {
//		encoderCount = (readArmEncoder() - encoderCount) * 100;		// [encoder counts / sec]
//		double rotationsSec = encoderCount / ENCODER_COUNTS_PER_REV;
//		radSec = rotationsSec * (2*PI);
//	}

//	return radSec;
}

double Arm::NativeUnitsToRadSec(double nativeUnits) {
	double nativeUnitsPerSec = nativeUnits * 10.0;
	double rotationsPerSec = nativeUnitsPerSec / ENCODER_COUNTS_PER_REV;

	return rotationsPerSec * (2*PI);
}

void Arm::SlewArmPos(void) {
	mArmTargetPosition += kSlewSpeed;
}

void Arm::SlewArmNeg(void) {
	mArmTargetPosition -= kSlewSpeed;
}

void Arm::SlewArmHold(void) {
	mArmTargetPosition = getArmPosition();
}

void Arm::testMode(int Idx) {
	frc::Timer m_timer;
	double FPGA = 0.0;
	m_timer.Reset();

	switch(Idx) {
	case 1: {
		FPGA = m_timer.GetFPGATimestamp();
		std::cout << FPGA << std::endl;
		if (FPGA < 5.0)
			setArmMotorSpeed(0.1);
		else if (FPGA >= 5.0 && FPGA < 10.0)
			setArmMotorSpeed(-0.1);
		else
			stopArmMotor();
		break;
	}

	case 2: {
// 		For constant position testing only
//		talonSRXArmMotor->Set(ControlMode::Position, 0.0);
		double alphaDesired;
		double sqWavePeriod = 10.0;
		double *intPart;
//		*intPart = 2.0;
		FPGA = m_timer.GetFPGATimestamp();
		std::cout << FPGA / sqWavePeriod << std::endl;
		//double fractPart = modf(FPGA / sqWavePeriod, intPart);		// MODF IS BS
		double fractPart = fmod(FPGA, sqWavePeriod);
		if (fractPart < 0.5*sqWavePeriod) {
			double alphaDesired_CAN_TALON = 0.0*DEG;
			double alphaDesired_CAN_TALON_native = alphaDesired_CAN_TALON / (2*PI) * ENCODER_COUNTS_PER_REV;
			talonSRXArmMotor->Set(ControlMode::Position, alphaDesired_CAN_TALON_native);
		}
		else {
			double alphaDesired_CAN_TALON = 10.0*DEG;
			double alphaDesired_CAN_TALON_native = alphaDesired_CAN_TALON / (2*PI) * ENCODER_COUNTS_PER_REV;
			talonSRXArmMotor->Set(ControlMode::Position, alphaDesired_CAN_TALON_native);
		}
		break;
	}

	case 3: {
		double alphaDesired;
		double sqWavePeriod = 10.0;
		double *intPart;
//		*intPart = 2.0;
		FPGA = m_timer.GetFPGATimestamp();
		std::cout << FPGA / sqWavePeriod << std::endl;
		//double fractPart = modf(FPGA / sqWavePeriod, intPart);		// MODF IS BS
		double fractPart = fmod(FPGA, sqWavePeriod);
		if (fractPart < 0.5*sqWavePeriod) {
			alphaDesired = 0.0*DEG;
		}
		else {
			alphaDesired = 45.0*DEG;
		}
		setArmPosition(alphaDesired);
		break;
	}

	}
}

void Arm::SlewArm(double slew) {
	slew = fmin(fmax(-1.0, slew), 1.0);
	mArmTargetPosition += (slew * kSlewSpeed);

}
