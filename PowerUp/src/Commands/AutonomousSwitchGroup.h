/*
 * AutonomousGearGroup.h
 *
 *  Created on: Feb 9, 2018
 *      Author: GEH-Magnet School 1
 */

#ifndef SRC_COMMANDS_AUTONOMOUSGEARGROUP_H_
#define SRC_COMMANDS_AUTONOMOUSGEARGROUP_H_

#include <Commands/CommandGroup.h>
#include "../ProfileData.h"


class AutonomousSwitchGroup: public frc::CommandGroup {
public:
	enum SwitchLocation {
			kBlueMiddleRight, //starts blue middle, goes to the right switch
			kBlueMiddleLeft,
			kRedMiddleRight,
			kRedMiddleLeft
		};

	AutonomousSwitchGroup(SwitchLocation loc);



private:

};

#endif /* SRC_COMMANDS_AUTONOMOUSGEARGROUP_H_ */
