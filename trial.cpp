/*
 * trial.cpp
 *
 *  Created on: 20.07.2014
 *      Author: meicron
 */

#include "environment.h"
#include "stream.h"
#include "map.h"
#include "trial.h"
using namespace std;

const int walkers = 1;
const int goals = 100;
const double m_radius = 100.;

Trial::Trial(Map* inmap){
	environment = new Environment(walkers, goals, m_radius);
	map = inmap;
	state.clear();
	entropy.clear();
	prob.clear();
	turn_rate.clear();
	abs_turn_rate.clear();

	add_streams();
}

Trial::~Trial() {
	delete environment;
}

void Trial::add_streams(){
}

void Trial::run(int time){
	map->reset();
	for(unsigned int ts = 0; ts < time; ts++){
		update();
	}
}

void Trial::update(){
	double command = map->update_map();
	state.push_back(command);
	environment->update(command);

	for(unsigned int i = 0; i < stream_list.size(); i++)
		stream_list.at(i)->write_data();
}

void Trial::print_data(){
	for(unsigned int i = 0; i < stream_list.size(); i++)
		stream_list.at(i)->print_data();
}

int main(){
	clock_t begin = clock();
	Map* map = new Map(1.0);
	Trial* trial = new Trial(map);
	for(int tr = 0; tr < 100; tr++)
		trial->run(1000);
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << elapsed_secs << " secs. Done." << endl;
	delete map;
	delete trial;
}
