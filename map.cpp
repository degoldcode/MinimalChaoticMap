/*
 * main.cpp
 *
 *  Created on: Jul 3, 2014
 *      Author: degoldschmidt
 */

#include <ctime>
#include <cmath>
#include <vector>
#include <cassert>


Map::Map(double param)
{
	rg = new RandGen(0.0, 1.0);
	pasemann = true;
	a_1 = 0.;
	a_2 = 0.;
	o_1 = rg->next();
	o_2 = rg->next();
	w_11 = 0.;
	w_12 = 0.;
	w_21 = 0.;
	b_1 = 0.;
	b_2 = 0.;
	set_weight(pasemann, param);
}

Map::~Map()
{

}

void Map::update_map()
{
	a_1 = update_node(b_1, w_11, w_12, o_1, o_2);
	a_2 = update_node(b_2, 0., w_21, o_2, o_1);
	o_1 = sigm(a_1);
	o_2 = sigm(a_2);
	o_avg.push_back(0.5 * (o_1 + o_2));
}

double Map::update_node(double bias, double self_con, double coup_con, double output, double input){
	return bias + self_con * output + coup_con * input;
}

double Map::sigm(double x){
	return 1./(1. + std::exp(-x));
}

void Map::set_weight(bool option, double param){
	if(option){
		w_11 = -20.;
		w_12 = 6.;
		w_21 = -6.;
		b_1 = -2.;
		b_2 = 3.;
	}
	else{
		w_11 = -22.;
		w_12 = 5.9;
		w_21 = -6.6;
		b_1 = -3.4;
		b_2 = 3.8;
	}
	w_11 = param;
}


