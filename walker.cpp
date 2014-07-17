/*
 * walker.cpp
 *
 *  Created on: Jul 17, 2014
 *      Author: degoldschmidt
 */

#include <cmath>
#include "walker.h"

Walker::Walker(){
	//*** Walker variables ***//
	x = 0.;
	y = 0.;
	phi = 0.;
	v = 0.1;
	k_phi = 4.;
	dphi = 0.0;
	abs_dphi = 0.0;
}

Walker::~Walker(){

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

void Walker::update_walker(double command){
	x += v*cos(phi);
	y += v*sin(phi);
	dphi = k_phi * (2.*command - 1.);
	phi += dphi;
	phi = bound_angle(phi);
	abs_dphi = std::abs(dphi);
}


//*** Goal variables ***//
const int goals = 100;
const double radius = 0.0;
std::vector<double> gx;
std::vector<double> gy;
double temp_r;
double temp_phi;
