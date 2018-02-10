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

AutonomousInitGroup::AutonomousInitGroup(const ProfileData* array) {
	AddSequential(new AutonomousMotionProfile(array));

}
