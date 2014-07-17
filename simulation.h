/*
 * simulation.h
 *
 *  Created on: 19.07.2014
 *      Author: meicron
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <vector>
#include "stream.h"
#include "trial.h"


class Simulation {
public:
	Simulation(double param);
	~Simulation();

	void run(int trials, int time);
	void update();
	void print_data();
	double avg(vector<double> input);
	double stdev(vector<double> input);

	Trial* trial;
	vector<Stream*> stream_list;
	Map* map;
};



#endif /* SIMULATION_H_ */
