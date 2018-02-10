/*
 * AutonomousGearGroup.cpp
 *
 *  Created on: Feb 9, 2018
 *      Author: GEH-Magnet School 1
 */

#include "AutonomousSwitchGroup.h"
#include "AutonomousMotionProfile.h"


//#include "AutonomousAllianceCmd.h"
#include "AutonomousBlendedMove.h"
//#include "AutonomousStop.h"
//#include "../Vision/VisionProcessing.h"
//#include "../automoves/BSMR.h"
//#include "../automoves/BSML.h"
//#include "../automoves/RSMR.h"
//#include "../automoves/RSML.h"


AutonomousSwitchGroup::AutonomousSwitchGroup() {
	// TODO Auto-generated constructor stub
	//AddParallel(new ArmInitialize());   //<--initialize subsystems
	int loc;
	//blendedmove calls and profiles depend on which location the robot is going to
	//This switch is CURRENTLY EMPTY as there are currently no trajectories
	switch (loc) {
	case 1:
		AddSequential(new AutonomousBlendedMove());
		break;
	case 2:
		AddSequential(new AutonomousBlendedMove());
		break;
	case 3:
		AddSequential(new AutonomousBlendedMove());
		break;
	case 4:
		AddSequential(new AutonomousBlendedMove());
	case 5:
		AddSequential(new AutonomousBlendedMove());
	case 6:
		AddSequential(new AutonomousBlendedMove());

		break;
	default:
		break;
	}

	AddSequential(new frc::WaitCommand(.3));


}
