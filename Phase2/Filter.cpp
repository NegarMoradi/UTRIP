#include"Filter.hpp"
#include"Header.hpp"
#include"Hotel.hpp"
#include"Exceptions.hpp"

using namespace std;

Filter::Filter() { ; }

CityFilter::CityFilter() 
{ 
	check_and_get_city(); 
}
vector<Hotel*> CityFilter::filter_hotels(vector<Hotel*>hotels)
{
	vector<Hotel*>new_hotels;
	for (int i = 0; i < hotels.size(); i++)
		if (hotels[i]->has_same_city(city) == true)
			new_hotels.push_back(hotels[i]);
	return new_hotels;
}
void CityFilter::check_and_get_city()
{
	string get_city;
	cin >> get_city;
	city = get_city;
	cout << OK << endl;
}

StarFilter::StarFilter(string command) 
{
	get_min_and_max_star(command);
	handle_exceptions();
	cout << OK << endl;
}
vector<Hotel*> StarFilter::filter_hotels(vector<Hotel*>hotels)
{
	vector<Hotel*>new_hotels;
	for (int i = 0; i < hotels.size(); i++)
		if (hotels[i]->filters_by_star(min_star, max_star) == true)
			new_hotels.push_back(hotels[i]);
	return new_hotels;
}
void StarFilter::get_min_and_max_star(string first_command)
{
	string command;
	int min_star_, max_star_;
	if (first_command == MIN_STAR)
	{
		cin >> min_star_ >> command >> max_star_;
		min_star = min_star_;
		if (command == MAX_STAR)
			max_star = max_star_;
		else
			throw Bad_request();
	}
	else if (first_command == MAX_STAR)
	{
		cin >> max_star_ >> command >> min_star_;
		max_star = max_star_;
		if (command == MIN_STAR)
			min_star = min_star_;
		else
			throw Bad_request();
	}
}
void StarFilter::handle_exceptions()
{
	if (min_star<ONE || min_star>FIVE)
		throw Bad_request();
	if (max_star<ONE || min_star>FIVE)
		throw Bad_request();
	if (min_star > max_star)
		throw Bad_request();
}

PriceFilter::PriceFilter(string command)
{ 
	get_min_and_max_price(command);
	handle_exceptions();
	cout << OK << endl;
}
vector<Hotel*> PriceFilter::filter_hotels(vector<Hotel*>hotels)
{
	vector<Hotel*>new_hotels;
	for (int i = 0; i < hotels.size(); i++)
		if (hotels[i]->filters_by_price(min_price, max_price) == true)
			new_hotels.push_back(hotels[i]);
	return new_hotels;
}
void PriceFilter::handle_exceptions()
{
	if (min_price < ZERO || max_price < ZERO)
		throw Bad_request();
	if (min_price > max_price)
		throw Bad_request();
}
void PriceFilter::get_min_and_max_price(string first_command)
{
	string command;
	float min_price_, max_price_;
	if (first_command == MIN_PRICE)
	{
		cin >> min_price_ >> command >> max_price_;
		min_price = min_price_;
		if (command == MAX_PRICE)
			max_price = max_price_;
		else
			throw Bad_request();
	}
	else if (first_command == MAX_PRICE)
	{
		cin >> max_price_ >> command >> min_price_;
		max_price = max_price_;
		if (command == MIN_PRICE)
			min_price = min_price_;
		else
			throw Bad_request();
	}
}
RoomFilter::RoomFilter(string command) 
{ 
	get_room_info(command);
	handle_exceptions();
	cout << OK << endl;
}
vector<Hotel*> RoomFilter::filter_hotels(vector<Hotel*>hotels)
{
	vector<Hotel*>new_hotels;
	for (int i = 0; i < hotels.size(); i++)
		if (hotels[i]->filters_by_room(type,quantity,check_in,check_out) == true)
			new_hotels.push_back(hotels[i]);
	return new_hotels;
}
void RoomFilter::get_room_info(string first_command)
{
	string type_;
	int quantity_, check_in_, check_out_;
	if (first_command == TYPE)
	{
		cin >> type_;
		type = type_;
	}
	else if (first_command == QUANTITY)
	{
		cin >> quantity_;
		quantity = quantity_;
	}
	else if (first_command == CHECK_IN)
	{
		cin >> check_in_;
		check_in = check_in_;
	}
	else if (first_command == CHECK_OUT)
	{
		cin >> check_out_;
		check_out = check_out_;
	}
	get_other_info();
}
vector<string> split(const string &s, char delim) {
	vector<string> result;
	istringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		result.push_back(item);
	}
	return result;
}
void RoomFilter::get_other_info()
{
	string command;
	cin.ignore();
	getline(cin, command);
	vector<string>split_space = split(command, SPACE);
	for (int i = 0; i < 6; i++)
	{
		if (split_space[i] == TYPE)
			type = split_space[i + 1];
		else if (split_space[i] == QUANTITY)
			quantity = stoi(split_space[i + 1]);
		else if (split_space[i] == CHECK_IN)
			check_in = stoi(split_space[i + 1]);
		else if (split_space[i] == CHECK_OUT)
			check_out = stoi(split_space[i + 1]);
		else
			throw Bad_request();
		i += ONE;
	}
}

void RoomFilter::handle_exceptions()
{
	bool check = false;
	if ((type == STANDARD) || (type == DELUXE) || (type == LUXURY) || (type == PREMIUM))
		check = true;
	if (check == false)
		throw Bad_request();
}

vector<Hotel*> Default_Budget::filter_hotels(vector<Hotel*>hotels)
{
	vector<Hotel*>new_hotels;
	for (int i = 0; i < hotels.size(); i++)
		if (hotels[i]->check_default_budget(calculate_average(), calculate_deviation()) == true)
			new_hotels.push_back(hotels[i]);
	return new_hotels;
}
Default_Budget::Default_Budget(vector<float>rooms_price)
{
	room_price = rooms_price;
}
float Default_Budget::calculate_average()
{
	float sum = ZERO;
	for (int i = 0; i < room_price.size(); i++)
		sum += room_price[i];
	return sum / room_price.size();
}
float Default_Budget::calculate_deviation()
{
	float average = calculate_average();
	float sum = ZERO;
	for (int i = 0; i < room_price.size(); i++)
	{
		float dif_from_av = room_price[i] - average;
		sum += pow(dif_from_av, TWO);
	}
	sum = sum / (room_price.size() - ONE);
	return sqrt(sum);
}