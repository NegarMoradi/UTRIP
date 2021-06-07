#include"Weight.hpp"
#include"Header.hpp"

using namespace std;

Weight::Weight(float ls, float cs, float ss, float fs, float vs)
{
	location = ls;
	cleanliness = cs;
	staff = ss;
	facilities = fs;
	value_of_money = vs;
}

void Weight::print(bool mood)
{
	if (mood == true)
	{
		float ls = (floorf(location * HUNDRED) / HUNDRED);
		float cs = (floorf(cleanliness * HUNDRED) / HUNDRED);
		float ss = (floorf(staff * HUNDRED) / HUNDRED);
		float fs = (floorf(facilities * HUNDRED) / HUNDRED);
		float vs = (floorf(value_of_money * HUNDRED) / HUNDRED);
		cout << ACTIVE << SPACE << TRUE << SPACE << LOCATION << SPACE << fixed << setprecision(TWO) << ls
			<< SPACE << CLEANLINESS << SPACE << cs << SPACE	<< STAFF << SPACE <<
			ss << SPACE << FACILITIES << SPACE << fs << SPACE << VALUE_FOR_MONEY <<
			SPACE << vs << endl;
	}
	else
		cout << ACTIVE << SPACE << FALSE << endl;
}
void Weight::print_for_estimated()
{
	float ls = (floorf(location * HUNDRED) / HUNDRED);
	float cs = (floorf(cleanliness * HUNDRED) / HUNDRED);
	float ss = (floorf(staff * HUNDRED) / HUNDRED);
	float fs = (floorf(facilities * HUNDRED) / HUNDRED);
	float vs = (floorf(value_of_money * HUNDRED) / HUNDRED);
	cout << LOCATION << SPACE << fixed << setprecision(TWO) << ls
		<< SPACE << CLEANLINESS << SPACE << cs << SPACE << STAFF << SPACE <<
		ss << SPACE << FACILITIES << SPACE << fs << SPACE << VALUE_FOR_MONEY <<
		SPACE << vs << endl;
}