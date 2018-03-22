/*
 * FilteredInput.h
 *
 *  Created on: Mar 21, 2018
 *      Author: nollchr
 */

#ifndef SRC_FILTEREDINPUT_H_
#define SRC_FILTEREDINPUT_H_

#include "WPILib.h"

// PIDSource wrapper to support filtering of a double value
class FilteredInput : public PIDSource {
public:
	FilteredInput();
	virtual ~FilteredInput();
	double PIDGet();
	void PIDSet(double val);
	void Update(double val);
private:
	double m_Value;
};

#endif /* SRC_FILTEREDINPUT_H_ */
