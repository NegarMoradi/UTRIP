#ifndef WEIGHT_HPP
#define WEIGHT_HPP "WEIGHT_HPP"

#include"Header.hpp"

class Weight
{
public:
	Weight(float ls, float cs, float ss, float fs, float vs);
	void print(bool mood);
	void print_for_estimated();
	float location;
	float cleanliness;
	float staff;
	float facilities;
	float value_of_money;
};
#endif 
