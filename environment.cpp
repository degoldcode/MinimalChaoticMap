/*
 * environment.cpp
 *
 *  Created on: Jul 17, 2014
 *      Author: degoldschmidt
 */


#include "environment.h"
using namespace std;

Environment::Environment(double num_walkers, double num_goals, double max_radius){
	stream.open("./data/goals.dat");
	for(unsigned int i = 0; i < num_walkers; i++){
		Walker * const walker = new Walker();
		walker_list.push_back(walker);
	}
	for(unsigned int i = 0; i < num_goals; i++){
		Goal * const goal = new Goal(max_radius);
		goal_list.push_back(goal);
	}
}

Environment::~Environment(){
	for(unsigned int i = 0; i < walker_list.size(); i++)
		delete walker_list.at(i);
	for(unsigned int i = 0; i < goal_list.size(); i++){
		stream << goal_list.at(i)->x_position << "\t" << goal_list.at(i)->y_position << "\t" << goal_list.at(i)->hit << endl;
		delete goal_list.at(i);
	}
	stream.close();
}

void Environment::update(double command){
	for(unsigned int i = 0; i < walker_list.size(); i++){
		walker_list.at(i)->update(command);
		for(unsigned int j = 0; j < goal_list.size(); j++)
			goal_list.at(j)->check_hit(walker_list.at(i)->x, walker_list.at(i)->y);
	}
}

int Environment::get_hits(){
	int sum = 0;
	for(unsigned int j = 0; j < goal_list.size(); j++)
		sum += goal_list.at(j)->hit;
	return sum;
}


