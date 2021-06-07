#ifndef USER_H
#define USER_H "USER_H"

#define ONE 1
#include "Header.h"
class Reserve;
class Filter;
class Hotel;
class User
{
public:
	User(std::string email_, std::string name_, std::string pass_);
	bool check_valid_email_and_name(std::string email_, std::string username_);
	bool check_email_and_pass(std::string email_, std::string pass_);
	std::string user_name;
	void amount(float amount_num);
	void count(int count_num);
	void count_for_smaller_size();
	void add_cityflter();
	void add_starfilter(std::string command);
	void add_roomfilter(std::string command);
	void add_pricefilter(std::string command);
	int filters_size() { return filters.size(); }
	void print_hotels(std::vector<Hotel*>hotels);
	void print_new_hotels(std::vector<Hotel*>new_hotels);
	void delete_filters();
	int get_reserves_size() { return reserves.size(); }
	void print_reserves();
	void delete_reserve(int id);
	std::string get_username() { return user_name; }
	void add_reserve(Hotel*reserve_hotel, std::string type, int quantity, int check_in, int check_out);
private:
	std::string email; 
	std::string password;
	float wallet;
	std::vector<float>bills;
	int next_id = 0;
	int reserve_id;
	std::vector<Reserve*>reserves;
	std::vector<Filter*>filters;
	void check_type(std::string type);
	void unique_hotels(std::vector<Hotel*>new_hotels);
	void check_credit(Hotel*reserve_hotel, std::string type, int quantity);
	void check_in_and_out(int in, int out);
	void check_filter_exist(std::string type);
};


#endif 
