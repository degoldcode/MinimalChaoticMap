/*
 * trial.cpp
 *
 *  Created on: 20.07.2014
 *      Author: meicron
 */

#include <cmath>
#include <cstdlib>
#include <iostream>
#include "trial.h"
using namespace std;

const int walkers = 1;
const double m_radius = 500.;
const double density = 0.0001;
const int goals = int(density * (M_PI * m_radius * m_radius));

Trial::Trial(Map* inmap){
	environment = new Environment(walkers, goals, m_radius);
	map = inmap;
	state.clear();
	entropy.clear();
	prob.clear();
	turn_rate.clear();
	abs_turn_rate.clear();
	success = 0;
	add_streams();
	factor = 0.4;
}

Trial::~Trial() {
	stream.close();
	delete environment;
}

void Trial::add_streams(){
	//stream.open("./data/walker.dat", ios_base::out);
	//stream.close();
	stream.open("./data/trial_bifur.dat", ios_base::out);
}

void Trial::run(int time){
	map->reset();
	for(unsigned int ts = 0; ts < time; ts++){
		update(ts);
	}
	stream << map->param_map << "\t" << map->out << "\t" << success << endl;
}

void Trial::update(int ts){
	double command = factor * (2.*map->update_map() - 1.);
	state.push_back(command);
	environment->update(command);
}
