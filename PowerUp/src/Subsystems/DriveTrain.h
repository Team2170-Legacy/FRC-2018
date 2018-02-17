// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "ctre/Phoenix.h"
#include "../ProfileData.h"




/**
 *
 *
 * @author ExampleAuthor
 */
class DriveTrain: public frc::Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<WPI_TalonSRX> talonSRXMasterLeft;
	std::shared_ptr<WPI_TalonSRX> talonSRXMasterRight;
	std::shared_ptr<frc::DifferentialDrive> differentialDrive1;
	std::shared_ptr<WPI_TalonSRX> talonSRXSlaveLeft1;
	std::shared_ptr<WPI_TalonSRX> talonSRXSlaveLeft2;
	std::shared_ptr<WPI_TalonSRX> talonSRXSlaveRight1;
	std::shared_ptr<WPI_TalonSRX> talonSRXSlaveRight2;
	std::shared_ptr<frc::PowerDistributionPanel> powerDistributionPanel;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	bool bDriveStraight = false;
	const bool kDriveVelocityMode = false;
	const double kDriveMaxVelocity = 1.0;
	bool mMotionProcessingActive = false;
	bool mReverseDrive = false;


	void InitMotors();

	void SetVelocityMode();
	void SetClosedLoopMode();
	void SetMotionProfileMode();
	void SetVoltagePercentMode();

	void SetMotorGains(int idx, int pidIdx);

	double MapStick(double stick);





public:
	DriveTrain();
	void InitDefaultCommand() override;
	void Periodic() override;
	void TankDrive(double leftSpeed, double rightSpeed);
	void CurvatureDrive(double xSpeed, double zRotation, bool isQuickTurn);
	void ArcadeDrive(double xSpeed, double zRotation, bool squaredInputs);

	// Motion Profile Support
	void FillProfileBuffer(std::shared_ptr<const ProfileData> LeftWheel);
	void FillProfileBuffer(std::shared_ptr<const ProfileData> LeftWheel,
			std::shared_ptr<const ProfileData> RightWheel);
	void ServiceMotionProfile();
	bool MotionProfileComplete();
	void SetChassisMode(ControlMode mode);
	void ResetChassisYaw();
	void SetMotionProfileState(SetValueMotionProfile mode);
	void SetChassisWheelVelocity(double left, double right);
	void TankDriveWithTriggers(double Left, double Right, double Trigger);
	void DriveStraight(bool Backwards);
	void DriveStraight(double Magnitude);
	void SetVelocity(double velocity);


	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
};

#endif
