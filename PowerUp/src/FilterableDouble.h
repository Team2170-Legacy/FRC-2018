/*
 * FilterableDouble.h
 *
 *  Created on: Mar 21, 2018
 *      Author: nollchr
 */

#ifndef SRC_FILTERABLEDOUBLE_H_
#define SRC_FILTERABLEDOUBLE_H_

#include "WPILib.h"

// PIDSource wrapper to support filtering of a double value
class FilterableDouble : public PIDSource {
public:
	FilterableDouble();
	virtual ~FilterableDouble();
	double PIDGet();
	void PIDSet(double val);
	void Update(double val);
private:
	double m_Value;
};

#endif /* SRC_FILTERABLEDOUBLE_H_ */
