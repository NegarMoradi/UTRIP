#include"Score.hpp"
#include"Header.hpp"

using namespace std;

Score::Score(string name_, float ls, float cs, float ss, float fs, float vs, float os)
{
	location = ls;
	cleanliness = cs;
	staff = ss;
	facilities = fs;
	value_of_money = vs;
	overral_rating = os;
	name = name_;
}
Score::Score(float ls, float cs, float ss, float fs, float vs, float os,string username_)
{
	location = ls;
	cleanliness = cs;
	staff = ss;
	facilities = fs;
	value_of_money = vs;
	overral_rating = os;
	username = username_;
}

void Score::print()
{
	float ls = (floorf(location * HUNDRED) / HUNDRED);
	float cs = (floorf(cleanliness * HUNDRED) / HUNDRED);
	float ss = (floorf(staff * HUNDRED) / HUNDRED);
	float fs = (floorf(facilities * HUNDRED) / HUNDRED);
	float vs = (floorf(value_of_money * HUNDRED) / HUNDRED);
	float os = (floorf(overral_rating * HUNDRED) / HUNDRED);
	cout << LOCATION_ << fixed << setprecision(TWO) << ls << endl;
	cout << CLEANLINESS_ << fixed << setprecision(TWO) << cs << endl;
	cout << STAFF_ << fixed << setprecision(TWO) << ss << endl;
	cout << FACILITIES_ << fixed << setprecision(TWO) << fs << endl;
	cout << VALUE_FOR_MONEY_ << fixed << setprecision(TWO) << vs << endl;
	cout << OVERALL_RATING_ << fixed << setprecision(TWO) << os << endl;
}