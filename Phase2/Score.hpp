#ifndef SCORE_HPP
#define SCORE_HPP "SCORE_HPP"

#include"Header.hpp"

class Score
{
public:
	Score(std::string name_, float ls, float cs, float ss, float fs, float vs, float os);
	Score(float ls, float cs, float ss, float fs, float vs, float os, std::string username);
	std::string username;
	std::string name;
	void print();
	float location;
	float cleanliness;
	float staff;
	float facilities;
	float value_of_money;
	float overral_rating;
};




#endif 
