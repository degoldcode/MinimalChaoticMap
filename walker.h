/*
 * walker.h
 *
 *  Created on: Jul 17, 2014
 *      Author: degoldschmidt
 */

#ifndef WALKER_H_
#define WALKER_H_

#include <iostream>
#include <fstream>
using namespace std;

class Walker {
public:
	Walker();
	~Walker();

	double bound_angle(double angle);
	void update(double command);

	double x;
	double y;
	double phi;
	double v;
	double k_phi;
	double dphi;
	double abs_dphi;

	ofstream stream;
	bool no_write;
};



#endif /* WALKER_H_ */
