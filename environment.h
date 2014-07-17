/*
 * environment.h
 *
 *  Created on: Jul 17, 2014
 *      Author: degoldschmidt
 */

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "walker.h"
#include "goal.h"
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Environment {
public:
	Environment(double num_walkers, double num_goals, double max_radius);
	~Environment();

	void update(double command);
	int get_hits();
	std::vector<Walker*> walker_list;
	std::vector<Goal*> goal_list;

	ofstream stream;
};



#endif /* ENVIRONMENT_H_ */
