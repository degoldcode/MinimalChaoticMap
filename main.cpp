/*
 * main.cpp
 *
 *  Created on: Jul 17, 2014
 *      Author: degoldschmidt
 */

#include "simulation.h"

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

Simulation* sim;

int main(){
	sim = new Simulation;
	while(param_val<=param_end){
		entropy.clear();
		map = new Map(param_val);
		for(unsigned int trial = 0; trial < trials; trial++){
			reset_param();
			for(unsigned int ts = 0; ts < T_end; ts++){

				//A) MAP
				//printf("ts = %4u\ta1 = %1.3f\ta2 = %1.3f\ta3 = %1.3f\to1 = %1.3f\to2 = %1.3f\to3 = %1.3f\n", ts, a_1, a_2, a_3, o_1, o_2, o_3);
				stspace << map->o_avg.back() << " ";
				//o_avg = logistic(o_avg, 1.);
				map->update_map();
				//o_avg = tent(o_avg, w_11);
				stspace << map->o_avg.back() << std::endl;


				//B) WALKER

				//printf("ts = %4u\to = %1.6f\tphi = %2.2f\n", ts, o_avg, phi);
				pos << ts << " " << x << " " << y << " " << phi << " " <<  k_phi * (2.*map->o_avg.back() - 1.)<< std::endl;

				//C) ANALYSIS
				for(unsigned int i = 0; i < num_bins; i++){
					if(map->o_avg.back() > bin_size*i && map->o_avg.back() < bin_size*(i+1))
						histo.at(i)++;
				}
				if(num_param == 1 && trials == 1 && ts%(T_end/10) == 0)
					printf("t = %4u\tout = %4.3f\n", ts, map->o_avg.back());
			}
			//Entropy
			for(unsigned int i = 0; i < num_bins; i++){
				if(histo.at(i)/(T_end*trials)!=0.)
					temp_entr += histo.at(i)/T_end * log2(histo.at(i)/T_end);
				prob += histo.at(i)/T_end;
			}
			prob_sum = prob;
			if(abs(prob_sum-1.0)>0.01)
				std::cout << prob_sum << std::endl;
			temp_entr *= -1.;
			entropy.push_back(temp_entr);
			if(num_param < 10)
				part = 1;
			else
				part = (num_param/10);
			bifurw << param_val << " " << map->o_avg.back() << std::endl;
		}
		paramw << param_val << " " << mean(map->o_avg) << " " << stdev(map->o_avg) << " " << turn_rate/T_end << " " << abs_turn_rate/T_end << " "  << mean(entropy) << std::endl;
		if(param%part == 0)
			printf("%3u %% |param = %f \t out = %4.3f\tmean = %4.3f\tstd = %4.3f\tskew = %4.3f\tturn = %4.3f\tentr = %4.3f\n",10*param/part, param_val, map->o_avg.back(), mean(map->o_avg), stdev(map->o_avg), skew(histo, bin_size, T_end), turn_rate/T_end, mean(entropy));
		param++;
		param_val = param_start + param * param_width;
	}
	for(unsigned int i = 0; i < num_bins; i++)
		histw << histo.at(i) << std::endl;
	for(unsigned int i = 0; i < num_bins; i++)
		hist3d << histo.at(i) << " ";
	hist3d << std::endl;

}

//
//std::ofstream bifurw;
//std::ofstream histw;
//std::ofstream hist3d;
//std::ofstream pos;
//std::ofstream stspace;
//std::ofstream paramw;
//
//
//
////*** Histogram variables ***//
//const int num_bins = 100;
//const double bin_size = 1./num_bins;
//std::vector<double> histo;
//std::vector<double> entropy;
//double temp_entr;
//double prob;
//double prob_sum = 1.;
//
//
//
////*** Functions ***//
//
//double thres(double x){
//	if(x >= 0.)
//		return 1.;
//	else
//		return 0.;
//}
//
//double lthres(double x){
//	if(x >= 0.)
//		return x;
//	else
//		return 0.;
//}
//
//
//
//double logistic(double input, double a){
//	return 4. * a * input * (1. - input);
//}
//
//double circle(double input, double T, double K){
//	double out;
//	out = input + T + (K/(2.*M_PI)) * sin(2. * M_PI * input);
//	while(out > 1.)
//		out = out - 1.0;
//	while(out < 0.)
//		out = out + 1.0;
//	return out;
//}
//
//double bernshift(double input, double a){
//	return fmod(a * input, 1.);
//}
//
//double min(double x, double y){
//	if(x==y)
//		return 0;
//	if(x<y)
//		return x;
//	else
//		return y;
//}
//
//double tent(double input, double a){
//	return a * min(input, 1. - input);
//}
//
//double mean(std::vector<double> input){
//	double sum = 0.0;
//	for(unsigned int i = 0; i < input.size(); i++){
//		sum += input.at(i);
//	}
//	return sum/input.size();
//}
//
//double stdev(std::vector<double> input){
//	double sum = 0.0;
//	double m = mean(input);
//	for(unsigned int i = 0; i < input.size(); i++){
//		sum += pow(input.at(i) - m, 2.);
//	}
//	return sum/input.size();
//}
//
//double skew(std::vector<double> input, double dx, double T){
//	double sum1,sum2;
//	sum1 = 0.0;
//	sum2 = 0.0;
//	for(unsigned int i = 0; i < input.size()/2; i++){
//		sum1 += input.at(i);
//		sum2 += input.at(i + input.size()/2);
//	}
//	sum1/=T;
//	sum2/=T;
//	return sum2-sum1;
//}
//
//void reset_param(){
//	rseed++;
//	generator.seed(rseed);
//	gx.resize(goals);
//	gy.resize(goals);
//	for (int i = 0; i < goals; i++) {
//		gx.at(i) = distribution(generator);
//		gy.at(i) = distribution(generator);
//	}
//	x = 0.;
//	y = 0.;
//	prob = 0.;
//	histo.clear();
//	histo.resize(num_bins);
//	turn_rate = 0.0;
//	abs_turn_rate = 0.0;
//	temp_entr = 0.0;
//	double rand_angle = 2. * M_PI * distribution(generator) - M_PI;
//	phi = bound(rand_angle);
//	//printf("Init\to_1 = %f\to_2 = %f\to_3 = %f\n", o_1, o_2);
//}
//
//Map* map;
//
//int main(){
//	bifurw.open("./data/pscan.dat");
//	histw.open("./data/histo.dat");
//	hist3d.open("./data/histo3d.dat");
//	pos.open("./data/pos.dat");
//	stspace.open("./data/stspace.dat");
//	paramw.open("./data/par.dat");
//
//	//std::cout << num_param << std::endl;
//	while(param_val<=param_end){
//		entropy.clear();
//		map = new Map(param_val);
//		for(unsigned int trial = 0; trial < trials; trial++){
//			reset_param();
//			for(unsigned int ts = 0; ts < T_end; ts++){
//
//				//A) MAP
//				//printf("ts = %4u\ta1 = %1.3f\ta2 = %1.3f\ta3 = %1.3f\to1 = %1.3f\to2 = %1.3f\to3 = %1.3f\n", ts, a_1, a_2, a_3, o_1, o_2, o_3);
//				stspace << map->o_avg.back() << " ";
//				//o_avg = logistic(o_avg, 1.);
//				map->update_map();
//				//o_avg = tent(o_avg, w_11);
//				stspace << map->o_avg.back() << std::endl;
//
//
//				//B) WALKER
//				x += v*cos(phi);
//				y += v*sin(phi);
//				phi += k_phi * (2.*map->o_avg.back() - 1.);
//				phi = bound(phi);
//				turn_rate += k_phi * (2.*map->o_avg.back() - 1.);
//				abs_turn_rate += std::abs(k_phi * (2.*map->o_avg.back() - 1.));
//				//printf("ts = %4u\to = %1.6f\tphi = %2.2f\n", ts, o_avg, phi);
//				pos << ts << " " << x << " " << y << " " << phi << " " <<  k_phi * (2.*map->o_avg.back() - 1.)<< std::endl;
//
//				//C) ANALYSIS
//				for(unsigned int i = 0; i < num_bins; i++){
//					if(map->o_avg.back() > bin_size*i && map->o_avg.back() < bin_size*(i+1))
//						histo.at(i)++;
//				}
//				if(num_param == 1 && trials == 1 && ts%(T_end/10) == 0)
//					printf("t = %4u\tout = %4.3f\n", ts, map->o_avg.back());
//			}
//			//Entropy
//			for(unsigned int i = 0; i < num_bins; i++){
//				if(histo.at(i)/(T_end*trials)!=0.)
//					temp_entr += histo.at(i)/T_end * log2(histo.at(i)/T_end);
//				prob += histo.at(i)/T_end;
//			}
//			prob_sum = prob;
//			if(abs(prob_sum-1.0)>0.01)
//				std::cout << prob_sum << std::endl;
//			temp_entr *= -1.;
//			entropy.push_back(temp_entr);
//			if(num_param < 10)
//				part = 1;
//			else
//				part = (num_param/10);
//			bifurw << param_val << " " << map->o_avg.back() << std::endl;
//		}
//		paramw << param_val << " " << mean(map->o_avg) << " " << stdev(map->o_avg) << " " << turn_rate/T_end << " " << abs_turn_rate/T_end << " "  << mean(entropy) << std::endl;
//		if(param%part == 0)
//			printf("%3u %% |param = %f \t out = %4.3f\tmean = %4.3f\tstd = %4.3f\tskew = %4.3f\tturn = %4.3f\tentr = %4.3f\n",10*param/part, param_val, map->o_avg.back(), mean(map->o_avg), stdev(map->o_avg), skew(histo, bin_size, T_end), turn_rate/T_end, mean(entropy));
//		param++;
//		param_val = param_start + param * param_width;
//	}
//	for(unsigned int i = 0; i < num_bins; i++)
//		histw << histo.at(i) << std::endl;
//	for(unsigned int i = 0; i < num_bins; i++)
//		hist3d << histo.at(i) << " ";
//	hist3d << std::endl;
//
//	histw.close();
//	hist3d.close();
//	pos.close();
//	bifurw.close();
//	stspace.close();
//	paramw.close();
//}


