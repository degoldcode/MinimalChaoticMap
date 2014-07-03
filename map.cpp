/*
 * main.cpp
 *
 *  Created on: Jul 3, 2014
 *      Author: degoldschmidt
 */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <random>
#include <ctime>

//*** Simulation variables & streams ***//
const int T_end = 500;
const int trials = 500;
const double param_start = -50.;
const double param_end = 25.;
const double param_width = 0.05;
int param = 0;
std::ofstream write;
std::ofstream histw;

//*** Random generator for initial values ***//
int rseed = time(NULL);
std::default_random_engine generator(rseed);
std::uniform_real_distribution<double> distribution(0.0,1.0);

//*** Network variables ***//
double a_1 = 0.;	//node activities
double a_2 = 0.;
double o_1 = distribution(generator);	//node outputs (o = f(a))
double o_2 = distribution(generator);
double o_avg = 0.;	//average node output
double w_11 = param_start;	//connection strengths between nodes (index are node<-node)
double w_12 = 5.9;
double w_21 = -6.6;
double b_1 = -3.4;	//biases
double b_2 = 3.8;

//*** Histogram variables ***//
const int num_bins = 1000;
const double bin_size = 1./num_bins;
double histo[num_bins];


//*** Functions ***//
double sigm(double x){
	return 1./(1. + std::exp(-x));
}

double map(double bias, double self_con, double coup_con, double output, double input){
	return bias + self_con * output + coup_con * input;
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

void reset_param(){
	rseed++;
	generator.seed(rseed);
	a_1 = 0.;
	a_2 = 0.;
	o_1 = distribution(generator);
	o_2 = distribution(generator);
	o_avg = 0.;
	//printf("o_1 = %f\to_2 = %f\n", o_1, o_2);
}

int main(){
	write.open("./data/results.dat");
	histw.open("./data/pscan.dat");

	while(w_11<param_end){
		param++;
		for(unsigned int trial = 0; trial < trials; trial++){
			reset_param();
			for(unsigned int ts = 0; ts < T_end; ts++){
				a_1 = map(b_1, w_11, w_12, o_1, o_2);
				a_2 = map(b_2, 0., w_21, o_2, o_1);
				o_1 = sigm(a_1);
				o_2 = sigm(a_2);
				//o_1 = circle(o_1, 1./3., 1.*M_PI);

				o_avg = 0.5 * (o_1 + o_2);
				/*			for(unsigned int i = 0; i < num_bins; i++){
				if(o_avg > bin_size*i && o_avg < bin_size*(i+1))
					histo[i]++;
			}*/
				if(trials == 1 && ts%(T_end/10) == 0)
					printf("t = %4u\tout = %4.3f\n", ts, o_avg);
			}
			if(param%(int(param_end)/10) == 0 && trial == 0)
				printf("param = %f\ttrial = %u\tout = %4.3f\n", w_11, trial, o_avg);
			histw << w_11 << " " << o_avg << std::endl;
		}
		w_11 += param_width;
	}

	/*for(unsigned int i = 0; i < num_bins; i++)
		histw << histo[i] << std::endl;*/

	histw.close();
	write.close();
}


