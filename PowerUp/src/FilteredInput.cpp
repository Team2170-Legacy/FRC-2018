/*
 * FilteredInput.cpp
 *
 *  Created on: Mar 21, 2018
 *      Author: nollchr
 */

#include "FilteredInput.h"

FilteredInput::FilteredInput() {
	// TODO Auto-generated constructor stub
	m_Value = 0.0;
}

FilteredInput::~FilteredInput() {
	// TODO Auto-generated destructor stub
}

double FilteredInput::PIDGet() {
	return m_Value;
}

void FilteredInput::PIDSet(double val) {
	m_Value = val;
}
