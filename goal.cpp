/*
 * goal.cpp
 *
 *  Created on: Jul 17, 2014
 *      Author: degoldschmidt
 */

#include <cmath>
#include <random>
#include "goal.h"
using namespace std;

Goal::Goal(double max_radius){
	distance_to_origin = max_radius * sqrt(rand(0.0, 1.0));
	angle_to_x_axis = 2 * M_PI * rand(0.0, 1.0);

	x_position = distance_to_origin * cos(angle_to_x_axis);
	y_position = distance_to_origin * sin(angle_to_x_axis);
	hit = 0;
}

Goal::~Goal(){

}

void Goal::check_hit(double x, double y){
	double rxsqr = pow(x-x_position, 2.);
	double rysqr = pow(y-y_position, 2.);
	double rdist = sqrt(rxsqr+rysqr);
	if(rdist < 0.2) //20 cm radius
		hit++;
}

double Goal::rand(double min, double max){
	static random_device e{};
	static uniform_real_distribution<double> d(min, max);
	return d(e);
}
