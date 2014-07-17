/*
 * goal.cpp
 *
 *  Created on: Jul 17, 2014
 *      Author: degoldschmidt
 */

#include <cmath>
#include "goal.h"
using namespace std;

Goal::Goal(double max_radius){
	rg_rad = new RandGen(0.0, max_radius);
	rg_angle = new RandGen(-M_PI, M_PI);

	distance_to_origin = rg_rad->next();
	angle_to_x_axis = rg_angle->next();

	x_position = distance_to_origin * cos(angle_to_x_axis);
	y_position = distance_to_origin * sin(angle_to_x_axis);

	hit = 0;
}

Goal::~Goal(){
	delete rg_rad;
	delete rg_angle;
}

void Goal::check_hit(double x, double y){
	double rxsqr = pow(x-x_position, 2.);
	double rysqr = pow(y-y_position, 2.);
	double rdist = sqrt(rxsqr+rysqr);
	if(rdist < 0.2) //20 cm
		hit++;
}
