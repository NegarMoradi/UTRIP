#include"Score.h"
#include"Header.h"

using namespace std;

Score::Score(string username_, float ls, float cs, float ss, float fs, float vs, float os)
{
	location = ls;
	cleanliness = cs;
	staff = ss;
	facilities = fs;
	value_of_money = vs;
	overral_rating = os;
	username = username_;
}