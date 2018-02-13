

#ifndef _PROFILEDATA_H
#define _PROFILEDATA_H

#include <cstddef>
#include <vector>
#include <array>


typedef std::vector<std::array<double, 3>> ProfileData;

// 45 degrees clockwise
extern const ProfileData Rotate45Clockwise;

// 90 degrees clockwise
extern const ProfileData Rotate90Clockwise;

// 180 degrees clockwise
extern const ProfileData Rotate180Clockwise;

// 45 degrees counterclockwise
extern const ProfileData Rotate45CounterClockwise;

// 90 degrees counterclockwise
extern const ProfileData Rotate90CounterClockwise;

// 180 degrees counterclockwise
extern const ProfileData Rotate180CounterClockwise;

// 9.5' forward
extern const ProfileData AutonomousMoveToBaseline;

// 63.3" backward toward gear peg
extern const ProfileData AutonomousMoveToGearPeg;

// 60 degrees clockwise
extern const ProfileData Rotate60Clockwise;


#endif
