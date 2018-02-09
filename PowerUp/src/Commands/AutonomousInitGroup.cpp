/*
 * AutonomousInitGroup.cpp
 *
 *  Created on: Feb 25, 2017
 *      Author: GEH-Magnet School 1
 */

#include "AutonomousInitGroup.h"
#include "AutonomousMotionProfile.h"

AutonomousInitGroup::AutonomousInitGroup() {
	// TODO Auto-generated constructor stub

}

AutonomousInitGroup::AutonomousInitGroup(frc::Command* cmd) {
	AddSequential(cmd);
}

AutonomousInitGroup::AutonomousInitGroup(const ProfileData* Left, const ProfileData* Right, double time) {
	//AddSequential(new AutonomousMotionProfile(array));
	AddSequential(new AutonomousMotionProfile(Left, Right, false, true, time));

}
