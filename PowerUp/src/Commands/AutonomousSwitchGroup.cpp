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
#include "../AutoMoves/BB_to_F.h"
//#include "AutonomousStop.h"
//#include "../Vision/VisionProcessing.h"
#include "../AutoMoves/BSMR.h"  //blue start middle to right
#include "../AutoMoves/BSML.h"  //blue start middle to left
#include "../AutoMoves/RSMR.h"  //red start middle to right
#include "../AutoMoves/RSML.h"  //red start middle to left
#include "ArmInitialize.h"


AutonomousSwitchGroup::AutonomousSwitchGroup(SwitchLocation loc) {
	// TODO Auto-generated constructor stub
	AddParallel(new ArmInitialize());   //<--initialize subsystems
	//blendedmove calls and profiles depend on which location the robot is going to
	//This switch is CURRENTLY EMPTY as there are currently no trajectories
	switch (loc) {
	case kBlueMiddleRight:
		//AddSequential(new AutonomousBlendedMove(&AutoMove_BSMR_L,
				//&AutoMove_BSMR_R, t_auto_end_BSMR, &VisionProcessing::));
		break;
	case kBlueMiddleLeft:
		AddSequential(new AutonomousBlendedMove());
		break;
	case kRedMiddleRight:
		AddSequential(new AutonomousBlendedMove());
		break;
	case kRedMiddleLeft:
		AddSequential(new AutonomousBlendedMove());
		break;
	default:

		break;
	}


	AddSequential(new frc::WaitCommand(.3));


}
