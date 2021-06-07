#ifndef FILTER_HPP
#define FILTER_HPP "FILTER_HPP"
#include"Header.hpp"

#define ZERO 0
#define STAR "star"
#define CITY "city"
#define PRICE "price"
#define ROOM "room"
#define DEFAULT_BUDGET "budget"
class Hotel;

class Filter
{
public:
	Filter();
	virtual std::vector<Hotel*>filter_hotels(std::vector<Hotel*>hotels) { return hotels; }
	virtual std::string return_type() = ZERO;
};

class CityFilter :public Filter
{
public:
	CityFilter();
	std::vector<Hotel*>filter_hotels(std::vector<Hotel*>hotels);
	void check_and_get_city();
	std::string return_type() { return "city"; }
private:
	std::string city;
	std::vector<Hotel*>new_hotels;
};

class StarFilter :public Filter
{
public:
	StarFilter(std::string command);
	std::vector<Hotel*>filter_hotels(std::vector<Hotel*>hotels);
	void get_min_and_max_star(std::string first_command);
	void handle_exceptions();
	std::string return_type() { return STAR; }
private:
	int min_star, max_star;
	std::vector<Hotel*>new_hotels;
};

class PriceFilter :public Filter
{
public:
	PriceFilter(std::string command);
	std::vector<Hotel*>filter_hotels(std::vector<Hotel*>hotels);
	void get_min_and_max_price(std::string first_command);
	void handle_exceptions();
	std::string return_type() { return PRICE; }
private:
	std::vector<Hotel*>new_hotels;
	float min_price;
	float max_price;
};

class RoomFilter :public Filter
{
public:
	RoomFilter(std::string command);
	std::vector<Hotel*>filter_hotels(std::vector<Hotel*>hotels);
	void get_room_info(std::string first_command);
	void handle_exceptions();
	void get_other_info();
	std::string return_type() { return ROOM; }
private:
	std::string type;
	int quantity;
	int check_in;
	int check_out;
	std::vector<Hotel*>new_hotels;
};

class Default_Budget :public Filter
{
public:
	Default_Budget(std::vector<float>rooms_price);
	std::vector<Hotel*>filter_hotels(std::vector<Hotel*>hotels);
	std::string return_type() { return DEFAULT_BUDGET; }
private:
	std::vector<float>room_price;
	float calculate_average();
	float calculate_deviation();
	std::vector<Hotel*>new_hotels;
};
#endif 
