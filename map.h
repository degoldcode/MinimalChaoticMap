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

#ifndef MAP_H_
#define MAP_H_

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

#endif /* MAP_H_ */
