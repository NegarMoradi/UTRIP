#ifndef USER_HPP
#define USER_HPP "USER_HPP"

#define ONE 1
#include "Header.hpp"
#include "Weight.hpp"

class Score;
class Reserve;
class Filter;
class Hotel;
class Default_Budget;

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
	Weight* return_weight() { return user_weight; }
	int filters_size() { return filters_num; }
	void print_hotels(std::vector<Hotel*>hotels);
	void print_new_hotels(std::vector<Hotel*>new_hotels);
	void delete_filters();
	int get_reserves_size() { return reserves.size(); }
	void print_reserves();
	void delete_reserve(int id);
	bool check_num_of_reserve();
	void add_score(std::string hotel_name, float ls, float cs, float ss, float fs, float vs, float os);
	void add_default_filter();
	void get_weight(bool mood);
	void set_weight(float location, float cleanliness, float staff, float facilities, float money);
	void print_by_default_filter(std::vector<Hotel*>hotels);
	std::string get_username() { return user_name; }
	int num_of_scores;
	std::vector<Score*>get_scores() { return scores; }
	void add_reserve(Hotel*reserve_hotel, std::string type, int quantity, int check_in, int check_out);
private:
	int filters_num;
	std::string email; 
	std::string password;
	float wallet;
	std::vector<float>bills;
	int next_id = 0;
	int reserve_id;
	std::vector<Reserve*>reserves;
	std::vector<Filter*>filters;
	std::vector<Score*>scores;
	void check_type(std::string type);
	void unique_hotels(std::vector<Hotel*>new_hotels);
	void check_credit(Hotel*reserve_hotel, std::string type, int quantity);
	void check_in_and_out(int in, int out);
	void check_filter_exist(std::string type);
	Default_Budget* default_filter;
	bool check_score_exist(std::string username);
	void replace_score(std::string username_, float ls, float cs, float ss, float fs, float vs, float os);
	std::vector<float>return_reserve_rooms_price();
	Weight* user_weight;
};


#endif 
