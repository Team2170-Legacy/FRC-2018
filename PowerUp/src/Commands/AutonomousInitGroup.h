/*
 * AutonomousInitGroup.h
 *
 *  Created on: Feb 25, 2017
 *      Author: GEH-Magnet School 1
 */

#ifndef SRC_COMMANDS_AUTONOMOUSINITGROUP_H_
#define SRC_COMMANDS_AUTONOMOUSINITGROUP_H_

#include <Commands/CommandGroup.h>
#include "../ProfileData.h"


class AutonomousInitGroup: public CommandGroup {
public:
	AutonomousInitGroup();
	AutonomousInitGroup(frc::Command* cmd);
	AutonomousInitGroup(const ProfileData* array);
	AutonomousInitGroup(const ProfileData* Left, const ProfileData* Right, double time);
};

#endif /* SRC_COMMANDS_AUTONOMOUSINITGROUP_H_ */
