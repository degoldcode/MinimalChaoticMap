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
const int T_end = 1000000;
std::ofstream write;
std::ofstream histw;

//*** Random generator for initial values ***//
std::default_random_engine generator(time(NULL));
std::uniform_real_distribution<double> distribution(0.0,1.0);

//*** Network variables ***//
double a_1 = 0.;	//node activities
double a_2 = 0.;
double o_1 = distribution(generator);	//node outputs (o = f(a))
double o_2 = distribution(generator);
double o_avg = 0.;	//average node output
double w_11 = -22.;	//connection strengths between nodes (index are node<-node)
double w_12 = 5.9;
double w_21 = -6.6;
double b_1 = -3.4;	//biases
double b_2 = 3.8;

//*** Histogram variables ***//
const int num_bins = 2;
const double bin_size = 1./num_bins;
double histo[num_bins];


//*** Functions ***//
double sigm(double x){
	return 1./(1. + std::exp(-x));
}

double map(double bias, double self_con, double coup_con, double output, double input){
	return bias + self_con * output + coup_con * input;
}

int main(){
	write.open("./data/results.dat");
	histw.open("./data/histo.dat");
	printf("o_1 = %f\to_2 = %f\n", o_1, o_2);

	for(unsigned int ts = 0; ts < T_end; ts++){
		a_1 = map(b_1, w_11, w_12, o_1, o_2);
		a_2 = map(b_2, 0., w_21, o_2, o_1);
		o_1 = sigm(a_1);
		o_2 = sigm(a_2);

		o_avg = 0.5 * (o_1 + o_2);
		for(unsigned int i = 0; i < num_bins; i++){
			if(o_avg > bin_size*i && o_avg < bin_size*(i+1))
				histo[i]++;
		}
		if(ts%(T_end/10) == 0)
			printf("t = %4u\tout = %4.3f\n", ts, o_avg);
	}
	for(unsigned int i = 0; i < num_bins; i++)
		histw << histo[i] << std::endl;

	histw.close();
	write.close();
}


