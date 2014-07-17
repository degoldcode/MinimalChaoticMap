/*
 * trial.h
 *
 *  Created on: 20.07.2014
 *      Author: meicron
 */

#ifndef TRIAL_H_
#define TRIAL_H_

using namespace std;

class Environment;
class Walker;
class Map;

class Trial {
public:
	Trial(Map* inmap);
	~Trial();

	void run(int time);
	void update();
	void print_data();
	void add_streams();
	double avg(vector<double> input);
	double stdev(vector<double> input);

	vector<double> state;
	vector<double> entropy;
	vector<double> prob;
	vector<double> turn_rate;
	vector<double> abs_turn_rate;

	Environment* environment;
	vector<Stream*> stream_list;
	Map* map;
};



#endif /* TRIAL_H_ */
