/*
 * walker.cpp
 *
 *  Created on: Jul 17, 2014
 *      Author: degoldschmidt
 */

#include <cmath>
#include "walker.h"
using namespace std;

Walker::Walker(){
	x = 0.;
	y = 0.;
	phi = 0.;
	v = 0.1;
	k_phi = 4.;
	dphi = 0.0;
	abs_dphi = 0.0;
	no_write = false;
	stream.open("./data/walker.dat", ios_base::out | ios_base::app);
}

Walker::~Walker(){
	stream.close();
}

double Walker::bound_angle(double phi){
	double rphi;
	rphi = phi;
	while(rphi > M_PI)
		rphi -= 2 * M_PI;
	while(rphi < - M_PI)
		rphi += 2 * M_PI;
	return rphi;
}

void Walker::update(double command){
	dphi = k_phi * command;
	phi += dphi;
	phi = bound_angle(phi);
	abs_dphi = std::abs(dphi);
	x += v*cos(phi);
	y += v*sin(phi);
	if(!no_write)
		stream << x << "\t" << y << "\t" << phi << "\t" << dphi << endl;
}
