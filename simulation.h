/*
 * simulation.h
 *
 *  Created on: 19.07.2014
 *      Author: meicron
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <vector>
#include "environment.h"
#include "stream.h"
#include "map.h"

class Environment;
class Walker;
class Map;

class Simulation {
public:
	Simulation(double param);
	~Simulation();

	void update();
	void print_data();

	Environment* environment;
	vector<Stream*> stream_list;
	Map* map;
};



#endif /* SIMULATION_H_ */
