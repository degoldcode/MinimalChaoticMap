/*
 * simulation.h
 *
 *  Created on: 19.07.2014
 *      Author: meicron
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <vector>
#include <iostream>
#include <fstream>
#include "map.h"
#include "trial.h"
using namespace std;

class Simulation {
public:
	Simulation(double param);
	~Simulation();

	void run(int trials, int time);
	double avg(vector<double> input);
	double stdev(vector<double> input);

	double success_rate;
	Trial* trial;
	Map* map;
	ofstream stream;
};



#endif /* SIMULATION_H_ */
