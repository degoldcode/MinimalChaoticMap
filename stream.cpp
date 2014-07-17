/*
 * stream.cpp
 *
 *  Created on: 19.07.2014
 *      Author: meicron
 */

#include <sstream>
#include <iostream>
#include <fstream>
#include "stream.h"
using namespace std;

Stream::Stream(string name)
{
	stream_name = name;
	stringstream ss;
	ss << "./data/" << stream_name << ".dat";
	stream.open(stream_name.c_str());
}

Stream::~Stream(){
	stream.close();
}

void Stream::add_data(double* data_value){
	data_list.push_back(data_value);
}

void Stream::write_data(){
	for(unsigned int i = 0; i < data_list.size(); i++)
		stream << data_list.at(i) << "\t";
	stream << endl;
}

void Stream::print_data(){
	for(unsigned int i = 0; i < data_list.size(); i++)
		cout << data_list.at(i) << "\t";
	cout << endl;
}
