/*
 * FilterableDouble.cpp
 *
 *  Created on: Mar 21, 2018
 *      Author: nollchr
 */

#include "FilterableDouble.h"

FilterableDouble::FilterableDouble() {
	// TODO Auto-generated constructor stub
	m_Value = 0.0;
}

FilterableDouble::~FilterableDouble() {
	// TODO Auto-generated destructor stub
}

double FilterableDouble::PIDGet() {
	return m_Value;
}

void FilterableDouble::PIDSet(double val) {
	m_Value = val;
}

// Same as PIDSet but not as confusing when reading code IMHO
void FilterableDouble::Update(double val) {
	PIDSet(val);
}
