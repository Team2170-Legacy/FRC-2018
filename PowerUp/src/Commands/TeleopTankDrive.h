// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef TELEOP_TANK_DRIVE_H
#define TELEOP_TANK_DRIVE_H


#include "Commands/Subsystem.h"
#include "../Robot.h"
#include "../FilteredInput.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class TeleopTankDrive: public frc::Command {
public:
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR
	TeleopTankDrive();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=VARIABLES


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=VARIABLES
	int driveMode;
	enum driveMode {
				tankDrive,
				arcadeDrive,
				curvatureDrive,
				xboxTankDrive,
				velocityMode
			};

	XboxController driverXbox;	// Xbox driver always USB 0
	std::shared_ptr<FilteredInput> ThrottleInput;
	std::shared_ptr<LinearDigitalFilter> ThrottleFilter;
};

#endif
