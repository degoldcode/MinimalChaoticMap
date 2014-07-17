/*
 * simulation.cpp
 *
 *  Created on: 19.07.2014
 *      Author: meicron
 */

#include <cstdlib>
#include <vector>
#include "simulation.h"
#include "timer.h"
using namespace std;

const int walkers = 1;
const int goals = 100;
const double m_radius = 100.;

class Map;
class Trial;

Simulation::Simulation(double param){
	map = new Map(param);
	success_rate = 0.0;
	stream.open("./data/walker.dat", ios_base::out);
	stream.close();
}

Simulation::~Simulation() {
	delete map;
}

void Simulation::run(int trials, int time){
	for(unsigned int trial_in = 0; trial_in < trials; trial_in++){
		trial = new Trial(map);
		trial->run(time);
		success_rate += trial->success;
		delete trial;
	}
	success_rate/=trials;
}

//*** Simulation variables & streams ***//
const int T_end = 100000;
const int num_trials = 1;
const double param_start = -20.0;
const double param_end = -20.0;
double param_val = param_start;
const double param_width = 0.5;

int param = 0;
int part;
int num_param = int((param_end - param_start)/param_width) + 1;

int main(){
	Timer timer(true);
	clock_t begin = clock();
	while(param_val<=param_end){
		Simulation* sim = new Simulation(param_val);
		sim->run(num_trials, T_end);
		printf("%3.2f\t%4.3f\n", param_val, sim->success_rate);
		param_val += param_width;
		delete sim;
	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	auto elapsed_secs_cl = timer.Elapsed();
	printf("%4.3f(%4.3f)s. Done.\n", elapsed_secs, elapsed_secs_cl.count()/1000.);
	//cout << elapsed_secs << " (" <<  << ") secs. Done." << endl;
}
