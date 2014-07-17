/*
 * stream.h
 *
 *  Created on: 19.07.2014
 *      Author: meicron
 */

#ifndef STREAM_H_
#define STREAM_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

class Stream {
public:
	Stream(string name);
	~Stream();

	void add_data(double* data_value);
	void write_data();
	void print_data();

	vector<double*> data_list;
	string stream_name;
	ofstream stream;
};



#endif /* STREAM_H_ */
