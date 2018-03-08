
// Select left or right switch based on field data
#ifndef DRIVETOSWITCH_H
#define DRIVETOSWITCH_H


#include "../Robot.h"

#include "Commands/ConditionalCommand.h"

class DriveToSwitchScore : public frc::ConditionalCommand {
public:
	DriveToSwitchScore();
	DriveToSwitchScore(frc::Command* left, frc::Command* right);

protected:
virtual bool Condition();
};

#endif
