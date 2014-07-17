/*
 * trial.h
 *
 *  Created on: 20.07.2014
 *      Author: meicron
 */

#ifndef TRIAL_H_
#define TRIAL_H_

#include <iostream>
#include <fstream>
#include "environment.h"
#include "map.h"
using namespace std;

class Environment;
class Walker;
class Map;

class Trial {
public:
	Trial(Map* inmap);
	~Trial();

	void run(int time);
	void update(int ts);
	void add_streams();
	double avg(vector<double> input);
	double stdev(vector<double> input);

	vector<double> state;
	vector<double> entropy;
	vector<double> prob;
	vector<double> turn_rate;
	vector<double> abs_turn_rate;
	int success;
	double factor;

	Environment* environment;
	Map* map;

	ofstream stream;
};



#endif /* TRIAL_H_ */
