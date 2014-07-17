/*
 * map.h
 *
 *  Created on: Jul 17, 2014
 *      Author: degoldschmidt
 */

#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <random>

#ifndef MAP_H_
#define MAP_H_

//*** Simulation variables & streams ***//
const int T_end = 50000;
const int trials = 1;
const double param_start = -18.0;
const double param_end = -18.0;
double param_val = param_start;
const double param_width = 0.01;


int param = 0;
int part;
int num_param = int((param_end - param_start)/param_width) + 1;
std::ofstream bifurw;
std::ofstream histw;
std::ofstream hist3d;
std::ofstream pos;
std::ofstream stspace;
std::ofstream paramw;


//*** Random generator for initial values ***//
int rseed = time(NULL);
std::default_random_engine generator(rseed);
std::uniform_real_distribution<double> distribution(0.0,1.0);

//*** Network variables ***//
class Map {
public:
	Map(double param);
	~Map();
	void update_map();
	double update_node(double bias, double self_con, double coup_con, double output, double input);
	double sigm(double x);
	void set_weight(bool option, double param);

	double a_1;					//node activities
	double a_2;
	double o_1;					//node outputs (o = f(a))
	double o_2;
	std::vector<double> o_avg;	//average node output
	bool pasemann;
	double w_11;
	double w_12;
	double w_21;
	double b_1;
	double b_2;
};

Map::Map(double param)
{
	pasemann = true;
	a_1 = 0.;
	a_2 = 0.;
	o_1 = distribution(generator);
	o_2 = distribution(generator);
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


//*** Histogram variables ***//
const int num_bins = 100;
const double bin_size = 1./num_bins;
std::vector<double> histo;
std::vector<double> entropy;
double temp_entr;
double prob;
double prob_sum = 1.;

//*** Walker variables ***//
double x = 0.;
double y = 0.;
double phi = 0.;
double v = 0.1;
double k_phi = 4.;
double turn_rate;
double abs_turn_rate;

//*** Goal variables ***//
const int goals = 100;
const double radius = 0.0;
std::vector<double> gx;
std::vector<double> gy;
double temp_r;
double temp_phi;

//*** Functions ***//
double bound(double phi){
	double rphi;
	rphi = phi;
	while(rphi > M_PI)
		rphi -= 2 * M_PI;
	while(rphi < - M_PI)
		rphi += 2 * M_PI;
	return rphi;
}

double thres(double x){
	if(x >= 0.)
		return 1.;
	else
		return 0.;
}

double lthres(double x){
	if(x >= 0.)
		return x;
	else
		return 0.;
}



double logistic(double input, double a){
	return 4. * a * input * (1. - input);
}

double circle(double input, double T, double K){
	double out;
	out = input + T + (K/(2.*M_PI)) * sin(2. * M_PI * input);
	while(out > 1.)
		out = out - 1.0;
	while(out < 0.)
		out = out + 1.0;
	return out;
}

double bernshift(double input, double a){
	return fmod(a * input, 1.);
}

double min(double x, double y){
	if(x==y)
		return 0;
	if(x<y)
		return x;
	else
		return y;
}

double tent(double input, double a){
	return a * min(input, 1. - input);
}

double mean(std::vector<double> input){
	double sum = 0.0;
	for(unsigned int i = 0; i < input.size(); i++){
		sum += input.at(i);
	}
	return sum/input.size();
}

double stdev(std::vector<double> input){
	double sum = 0.0;
	double m = mean(input);
	for(unsigned int i = 0; i < input.size(); i++){
		sum += pow(input.at(i) - m, 2.);
	}
	return sum/input.size();
}

double skew(std::vector<double> input, double dx, double T){
	double sum1,sum2;
	sum1 = 0.0;
	sum2 = 0.0;
	for(unsigned int i = 0; i < input.size()/2; i++){
		sum1 += input.at(i);
		sum2 += input.at(i + input.size()/2);
	}
	sum1/=T;
	sum2/=T;
	return sum2-sum1;
}

void reset_param(){
	rseed++;
	generator.seed(rseed);
	gx.resize(goals);
	gy.resize(goals);
	for (int i = 0; i < goals; i++) {
		gx.at(i) = distribution(generator);
		gy.at(i) = distribution(generator);
	}
	x = 0.;
	y = 0.;
	prob = 0.;
	histo.clear();
	histo.resize(num_bins);
	turn_rate = 0.0;
	abs_turn_rate = 0.0;
	temp_entr = 0.0;
	double rand_angle = 2. * M_PI * distribution(generator) - M_PI;
	phi = bound(rand_angle);
	//printf("Init\to_1 = %f\to_2 = %f\to_3 = %f\n", o_1, o_2);
}

#endif /* MAP_H_ */
