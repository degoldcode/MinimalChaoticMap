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
#include <vector>

//*** Simulation variables & streams ***//

const int T_end = 20000;
const int trials = 1;
double param_start = -20.0;
double param_end = -20.0;
const double param_width = 0.2;

int param = 0;
int part;
int num_param = int((param_end - param_start)/param_width) + 1;
std::ofstream bifurw;
std::ofstream histw;
std::ofstream hist3d;
std::ofstream pos;
std::ofstream stspace;


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

void setWeight(bool option){
	if(option){
		w_11 = -20.;
		w_12 = 6.;
		w_21 = -6.;
		b_1 = -2.;
		b_2 = 3.;
		if(trials == 1){
			param_start = -20.0;
			param_end = -20.0;
		}
	}
	else{
		w_11 = -22.;
		w_12 = 5.9;
		w_21 = -6.6;
		b_1 = -3.4;
		b_2 = 3.8;
		if(trials == 1){
			param_start = -22.0;
			param_end = -22.0;
		}
	}
}


//*** Histogram variables ***//
const int num_bins = 100;
const double bin_size = 1./num_bins;
std::vector<double> histo;

//*** Walker variables ***//
double x = 0.;
double y = 0.;
double phi = 0.;
double v = 0.1;
double k_phi = 4.;
double turn_rate;


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

double sigm(double x){
	return 1./(1. + std::exp(-x));
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
	printf("dx = %f\n",dx);
	for(unsigned int i = 0; i < input.size()/2; i++){
		sum1 += input.at(i);
		sum2 += input.at(i + input.size()/2);
	}
	sum1/=T;
	sum2/=T;
	printf("SUM = %f\n",sum1+sum2);
	return sum2-sum1;
}

void reset_param(){
	rseed++;
	generator.seed(rseed);
	a_1 = 0.;
	a_2 = 0.;
	a_3 = 0.;
	o_1 = distribution(generator);
	o_2 = distribution(generator);
<<<<<<< HEAD
	o_3 = 0.;
	o_avg.resize(0);
	o_avg.push_back(0.5 * (o_1 + o_2));
	histo.resize(num_bins);
	x = 0.;
	y = 0.;
	turn_rate = 0.0;
	double rand_angle = 2. * M_PI * distribution(generator) - M_PI;
	phi = bound(rand_angle);
	printf("Init\to_1 = %f\to_2 = %f\to_3 = %f\n", o_1, o_2, o_3);
}

int main(){
	bifurw.open("./data/pscan.dat");
	histw.open("./data/histo.dat");
	hist3d.open("./data/histo3d.dat");
	pos.open("./data/pos.dat");
	stspace.open("./data/stspace.dat");

	setWeight(pasemann);
	//std::cout << num_param << std::endl;
	while(w_11<=param_end){
		param++;
		for(unsigned int trial = 0; trial < trials; trial++){
			reset_param();
			for(unsigned int ts = 0; ts < T_end; ts++){

				//A) MAP
				a_1 = map(b_1, w_11, w_12, o_1, o_2);
				a_2 = map(b_2, 0., w_21, o_2, o_1);
				o_1 = sigm(a_1);
				o_2 = sigm(a_2);
				//printf("ts = %4u\ta1 = %1.3f\ta2 = %1.3f\ta3 = %1.3f\to1 = %1.3f\to2 = %1.3f\to3 = %1.3f\n", ts, a_1, a_2, a_3, o_1, o_2, o_3);
				stspace << o_avg.back() << " ";
				//o_avg = logistic(o_avg, 1.);
				o_avg.push_back(0.5 * (o_1 + o_2));
				//o_avg = tent(o_avg, w_11);
				stspace << o_avg.back() << std::endl;


				//B) WALKER
				x += v*cos(phi);
				y += v*sin(phi);
				phi += k_phi * (2.*o_avg.back() - 1.);
				phi = bound(phi);
				turn_rate += k_phi * (2.*o_avg.back() - 1.);
				//printf("ts = %4u\to = %1.6f\tphi = %2.2f\n", ts, o_avg, phi);
				pos << ts << " " << x << " " << y << " " << phi << " " <<  k_phi * (2.*o_avg.back() - 1.)<< std::endl;

				//C) ANALYSIS
				for(unsigned int i = 0; i < num_bins; i++){
					if(o_avg.back() > bin_size*i && o_avg.back() < bin_size*(i+1))
						histo.at(i)++;
				}
				if(num_param == 1 && trials == 1 && ts%(T_end/10) == 0)
					printf("t = %4u\tout = %4.3f\n", ts, o_avg.back());
			}
			if(num_param < 10)
				part = 1;
			else
				part = (num_param/10);
			if(param%part == 0 && trial == 0)
				printf("param = %f\ttrial = %u\tout = %4.3f\tmean = %4.3f\tstd = %4.3f\tskew = %4.3f\tturn = %4.3f\n", w_11, trial, o_avg.back(), mean(o_avg), stdev(o_avg), skew(histo, bin_size, T_end), turn_rate/T_end);
			bifurw << w_11 << " " << o_avg.back() << std::endl;
		}
		for(unsigned int i = 0; i < num_bins; i++)
			hist3d << histo[i]/500. << " ";
		hist3d << std::endl;
		w_11 += param_width;
	}
	for(unsigned int i = 0; i < num_bins; i++)
		histw << histo.at(i) << std::endl;
	for(unsigned int i = 0; i < num_bins; i++)
		hist3d << histo.at(i) << " ";
	hist3d << std::endl;

	histw.close();
	hist3d.close();
	pos.close();
	bifurw.close();
	stspace.close();
}


