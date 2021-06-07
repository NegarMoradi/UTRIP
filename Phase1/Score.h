#ifndef SCORE_H
#define SCORE_H "SCORE_H"

#include"Header.h"

class Score
{
public:
	Score(std::string username_, float ls, float cs, float ss, float fs, float vs, float os);
	float location;
	float cleanliness;
	float staff;
	float facilities;
	float value_of_money;
	float overral_rating;
	std::string username;
};




#endif 
