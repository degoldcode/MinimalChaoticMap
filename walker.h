/*
 * walker.h
 *
 *  Created on: Jul 17, 2014
 *      Author: degoldschmidt
 */

#ifndef WALKER_H_
#define WALKER_H_

class Walker {
public:
	Walker();
	~Walker();

	double bound_angle(double angle);
	void update_walker(double command);

	double x;
	double y;
	double phi;
	double v;
	double k_phi;
	double dphi;
	double abs_dphi;
};



#endif /* WALKER_H_ */
