/*
 * goal.cpp
 *
 *  Created on: Jul 17, 2014
 *      Author: degoldschmidt
 */

#include <cmath>
#include "goal.h"

Goal::Goal(double max_radius){
	rg_rad = new RandGen(0.0, max_radius);
	rg_angle = new RandGen(-M_PI, M_PI);

	distance_to_origin = rg_rad->next();
	angle_to_x_axis = rg_angle->next();

	x_position = distance_to_origin * cos(angle_to_x_axis);
	y_position = distance_to_origin * sin(angle_to_x_axis);

	hit = false;
}

