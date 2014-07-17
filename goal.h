/*
 * goal.h
 *
 *  Created on: Jul 17, 2014
 *      Author: degoldschmidt
 */

#ifndef GOAL_H_
#define GOAL_H_

#include "randgen.h"

class Goal {
public:
	Goal(double max_radius);
	~Goal();

	double x_position;
	double y_position;
	double distance_to_origin;
	double angle_to_x_axis;

	RandGen* rg_rad;
	RandGen* rg_angle;

	bool hit;
};



#endif /* GOAL_H_ */
