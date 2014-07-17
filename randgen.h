/*
 * randgen.h
 *
 *  Created on: Jul 17, 2014
 *      Author: degoldschmidt
 */

#include <ctime>
#include <random>
using namespace std;

#ifndef RANDGEN_H_
#define RANDGEN_H_

class RandGen {
private:
    // Types
    typedef mt19937									Engine;
    typedef uniform_real_distribution<double>       Distribution;
    typedef variate_generator<Engine, Distribution> Generator;

    // To hold the generator
    Generator* _gen;

public:
	RandGen( double minVal, double maxVal )
	{
		rseed = time(NULL);
		_gen = new Generator( Engine( rseed ), Distribution( minVal, maxVal ) );
	}
	~RandGen()
	{
	        delete _gen;
	}
    double next()
    {
    	rseed++;
        return (*_gen)();
    }

	int rseed;
};




#endif /* RANDGEN_H_ */
