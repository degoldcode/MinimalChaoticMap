/*
 * simulation.cpp
 *
 *  Created on: 19.07.2014
 *      Author: meicron
 */

#include <vector>
#include "simulation.h"
#include "trial.h"
using namespace std;

const int walkers = 1;
const int goals = 100;
const double m_radius = 100.;

Simulation::Simulation(double param){
	environment = new Environment(walkers, goals, m_radius);
	map = new Map(param);
}

Simulation::~Simulation() {
	delete environment;
	delete map;
}

void Simulation::run(int trials, int time){
	for(unsigned int trial = 0; trial < trials; trial++){
		start_trial();
		for(unsigned int ts = 0; ts < time; ts++){
			update();
		}
		end_trial();
	}
}

void Simulation::update(){
	double command = map->update_map();
	environment->update(command);
	for(unsigned int i = 0; i < stream_list.size(); i++)
		stream_list.at(i)->write_data();
}

void Simulation::print_data(){
	for(unsigned int i = 0; i < stream_list.size(); i++)
		stream_list.at(i)->print_data();
}
