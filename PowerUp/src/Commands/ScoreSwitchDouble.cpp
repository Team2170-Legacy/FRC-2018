/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ScoreSwitchDouble.h"
#include "AutonomousMotionProfile.h"
#include "DriveToSwitchScore.h"
#include "PickupCube.h"
#include "OuttakeOn.h"
#include "IntakeOn.h"
#include "IntakeOpen.h"
#include "ArmSetPosition.h"
#include "../AutoMoves/SecondCubeLeftSwitch.h"
#include "../AutoMoves/SecondCubeLeftSwitchFoward.h"
#include "../AutoMoves/SecondCubeLeftSwitchv2.h"
#include "../AutoMoves/SecondCubeLeftSwitchForwardv2.h"
#include "../AutoMoves/SecondCubeRightSwitchv2.h"
#include "../AutoMoves/SecondCubeRightSwitchForwardv2.h"

ScoreSwitchDouble::ScoreSwitchDouble() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	// To run multiple commands at the same time,
	// use AddParallel()
	// e.g. AddParallel(new Command1());
	//      AddSequential(new Command2());
	// Command1 and Command2 will run in parallel.

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.
	AddSequential(new IntakeOpen());
	AddParallel(new ArmSetPosition(-90));
	AddSequential(new DriveToSwitchScore(
			new AutonomousMotionProfile(&AutoMove_SecondCubeLeftSwitchv2_L,
				&AutoMove_SecondCubeLeftSwitchv2_R),
			new AutonomousMotionProfile(&AutoMove_SecondCubeLeftSwitchv2_L,
				&AutoMove_SecondCubeLeftSwitchv2_R)));

	AddSequential(new IntakeOn(true));
	// Pick up second cube
	AddSequential(new PickupCube());
	// Advance to fence of switch
	AddSequential(new DriveToSwitchScore(
			new AutonomousMotionProfile(&AutoMove_SecondCubeLeftSwitchForwardv2_L,
				&AutoMove_SecondCubeLeftSwitchForwardv2_R),
			new AutonomousMotionProfile(&AutoMove_SecondCubeRightSwitchForwardv2_L,
				&AutoMove_SecondCubeRightSwitchForwardv2_R)));
	// Deposit cube
	AddSequential(new OuttakeOn(1.0));			// Outtake on for 1 second
}

ScoreSwitchDouble::ScoreSwitchDouble(frc::Command* left, frc::Command* right) {
	// Score first cube on side of active switch
	AddSequential(new DriveToSwitchScore(left, right));

	// Position to pick up second cube
	AddParallel(new IntakeOpen());
	AddParallel(new ArmSetPosition(-90));
	AddSequential(new DriveToSwitchScore(
			new AutonomousMotionProfile(&AutoMove_SecondCubeLeftSwitchv2_L,
				&AutoMove_SecondCubeLeftSwitchv2_R),
			new AutonomousMotionProfile(&AutoMove_SecondCubeRightSwitchv2_L,
				&AutoMove_SecondCubeRightSwitchv2_R)));

	// Pick up second cube
	AddSequential(new PickupCube());
	// Advance to fence of switch
	AddSequential(new DriveToSwitchScore(
			new AutonomousMotionProfile(&AutoMove_SecondCubeLeftSwitchForwardv2_L,
				&AutoMove_SecondCubeLeftSwitchForwardv2_R),
			new AutonomousMotionProfile(&AutoMove_SecondCubeLeftSwitchForwardv2_L,
				&AutoMove_SecondCubeLeftSwitchForwardv2_R)));
	// Deposit cube
	AddSequential(new OuttakeOn(0.5));			// Outtake on
}
