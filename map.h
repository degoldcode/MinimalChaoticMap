/*
 * map.h
 *
 *  Created on: Jul 17, 2014
 *      Author: degoldschmidt
 */

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
double a_1 = 0.;						//node activities
double a_2 = 0.;
double o_1 = distribution(generator);	//node outputs (o = f(a))
double o_2 = distribution(generator);
std::vector<double> o_avg;						//average node output
bool pasemann = true;
double w_11;
double w_12;
double w_21;
double b_1;
double b_2;

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



#endif /* MAP_H_ */
