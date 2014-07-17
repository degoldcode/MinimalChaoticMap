/*
 * randgen.h
 *
 *  Created on: Jul 17, 2014
 *      Author: degoldschmidt
 */

#include <random>
using namespace std;

#ifndef RANDGEN_H_
#define RANDGEN_H_

class RandomGenerator {
private:
    // Types
    typedef mt19937									Engine;
    typedef uniform_real_distribution<double>       Distribution;
    typedef variate_generator<Engine, Distribution> Generator;

    // To hold the generator
    Generator* _gen;
public:
	RandomGenerator();
	~RandomGenerator();

	int rseed;
};




#endif /* RANDGEN_H_ */
