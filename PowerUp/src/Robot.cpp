// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Robot.h"
#include "Commands/ArmInitialize.h"
#include "Commands/NoCommand.h"
#include "Commands/ScoreSwitch.h"
#include "Commands/AutonomousMotionProfile.h"
#include "Commands/DriveToSwitchScore.h"
#include "AutoMoves/Straight.h"
#include "AutoMoves/Arc.h"

#include "AutoMoves/RSMLF.h"
#include "AutoMoves/RSMRF.h"
#include "AutoMoves/RSLLF.h"
#include "AutoMoves/RSLRF.h"
#include "AutoMoves/RSRLF.h"
#include "AutoMoves/RSRRF.h"

#include "AutoMoves/RSMLS.h"
#include "AutoMoves/RSMRS.h"
#include "AutoMoves/RSLLS.h"
#include "AutoMoves/RSLRS.h"
#include "AutoMoves/RSRLS.h"
#include "AutoMoves/RSRRS.h"

#include "AutoMoves/RSMR.h"
#include "AutoMoves/RSRL.h"
#include <iostream>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<DriveTrain> Robot::driveTrain;
std::shared_ptr<Intake> Robot::intake;
std::shared_ptr<Arm> Robot::arm;
std::unique_ptr<OI> Robot::oi;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<frc::Timer> Robot::BlendTimer;

void Robot::RobotInit() {
	RobotMap::init();
	BlendTimer.reset(new frc::Timer());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    driveTrain.reset(new DriveTrain());
    intake.reset(new Intake());
    arm.reset(new Arm());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi.reset(new OI());

	// Add commands to Autonomous Sendable Chooser
	chooser.AddDefault("A Do Nothing", new NoCommand());
	chooser.AddObject("B Drive Straight",
			new AutonomousMotionProfile(&AutoMove_Straight_L, &AutoMove_Straight_R));
	chooser.AddObject("C Middle Start Score Front",new DriveToSwitchScore (
			new ScoreSwitch(&AutoMove_RSMLF_L, &AutoMove_RSMLF_R),
			new ScoreSwitch(&AutoMove_RSMRF_L, &AutoMove_RSMRF_R)));
	chooser.AddObject("D Middle Start Score Side", new DriveToSwitchScore (
			new ScoreSwitch(&AutoMove_RSMLS_L, &AutoMove_RSMLS_R),
			new ScoreSwitch(&AutoMove_RSMRS_L, &AutoMove_RSMRS_R)));
	chooser.AddObject("E Left Start Score Front",new DriveToSwitchScore (
			new ScoreSwitch(&AutoMove_RSLLF_L, &AutoMove_RSLLF_R),
			new ScoreSwitch(&AutoMove_RSLRF_L, &AutoMove_RSLRF_R)));
	chooser.AddObject("F Left Start Score Side",new DriveToSwitchScore (
			new ScoreSwitch(&AutoMove_RSLLS_L, &AutoMove_RSLLS_R),
			new ScoreSwitch(&AutoMove_RSLRS_L, &AutoMove_RSLRS_R)));
	chooser.AddObject("G Right Start Score Font",new DriveToSwitchScore (
			new ScoreSwitch(&AutoMove_RSRLS_L, &AutoMove_RSRLS_R),
			new ScoreSwitch(&AutoMove_RSRRS_L, &AutoMove_RSRRS_R)));
	chooser.AddObject("H Right Start Score Side",new DriveToSwitchScore (
			new ScoreSwitch(&AutoMove_RSRLS_L, &AutoMove_RSMLS_R),
			new ScoreSwitch(&AutoMove_RSRRS_L, &AutoMove_RSRRS_R)));
	SmartDashboard::PutData("Auto Modes", &chooser);

	Robot::arm->resetArmEncoder();
	LiveWindow::GetInstance()->DisableAllTelemetry();

	isPracticeBot = Preferences::GetInstance()->GetBoolean("Practice Bot", false);
}

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){
}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
	UpdateSmartDash();
}

void Robot::AutonomousInit() {
	autonomousCommand = chooser.GetSelected();

	if (autonomousCommand != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand != nullptr)
		autonomousCommand->Cancel();
	UpdateSmartDash();
}

void Robot::TeleopPeriodic() {
	frc::Scheduler::GetInstance()->Run();
	UpdateSmartDash();
}

START_ROBOT_CLASS(Robot);

void Robot::UpdateSmartDash() {
	double velocity = Robot::arm->getArmMotorVelocity();
	double velocityRadSec = Robot::arm->NativeUnitsToRadSec(velocity);
	SmartDashboard::PutNumber("Arm Speed [rad/sec]", velocityRadSec);
	SmartDashboard::PutBoolean("Limit Switch Front", Robot::arm->readLimitSwitchFront());
	SmartDashboard::PutBoolean("Reverse Direction", Robot::driveTrain->isReverseDrive());
	SmartDashboard::PutBoolean("Limit Switch Back", Robot::arm->readLimitSwitchBack());
	SmartDashboard::PutNumber("Arm Encoder Count", Robot::arm->readArmEncoder());
	SmartDashboard::PutNumber("Arm Position [degrees]", Robot::arm->getArmPosition()/DEG);

}

