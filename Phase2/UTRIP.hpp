#ifndef UTRIP_HPP 
#define UTRIP_HPP "UTRIP_HPP"

#include"Header.hpp"
class Hotel;
class Input;
class User;
class Post;
class Get;
class Request;
class Weight;

class UTRIP
{
public:
	UTRIP(std::vector<std::string> file_name);
	void get_put();
	void getting_input(std::string command);
	void post_demand();
	void get_demand();
	void check_question_mark();
	void signup();
	void check_email_and_username(std::string email_, std::string username_);
	void login();
	void logout();
	void wallet();
	void wallet_handle(std::string request);
	std::vector<std::string> split(const std::string &s, char delim);
	void get_hotels(std::vector<std::string>demand);
	void sort_hotels();
	void print_all_hotels();
	void print_filter_hotels();
	void print_one_hotel(std::vector<std::string> id);
	void filters();
	void choose_filter(std::string command);
	void delete_command();
	void reserves();
	void get_info_for_reserve(std::vector<std::string>command);
	void comments();
	void add_comment(std::vector<std::string>demand);
private:
	User* main_user;
	std::vector<User*>users;
	std::vector<Hotel*>hotels;
	Input* getput;
	Get* get;
	Post* post;
	Request* demand;
	User* find_user(std::string email_, std::string pass_);
	void check_main_user();
	void check_main_user_for_another();
	void find_and_print_hotel(std::string id);
	Hotel* find_hotel(std::string id);
	void get_reserves();
	bool sorting;
	void sorting_hotels();
	void check_property(std::string value);
	void check_order(std::string value);
	void sort_checks(std::vector<std::string> demand);
	void sort_handling(std::string property, std::string order);
	void sort_hotels_by_id(std::string order);
	void sort_hotels_by_name(std::string order);
	void sort_hotels_by_star_rating(std::string order);
	void sort_hotels_by_city(std::string order);
	void sort_hotels_by_sp(std::string order);
	void sort_hotels_by_dp(std::string order);
	void sort_hotels_by_lp(std::string order);
	void sort_hotels_by_pp(std::string order);
	void sort_hotels_by_ap(std::string order);
	void sort_hotels_by_ro(std::string order);
	void sort_hotels_by_rp(std::string order);
	void set_rating_personal();
	void print_without_default_budget();
	void check_filter_default_budget();
	bool default_budget;
	void print_by_default_budget_filter();
	void delete_reserve();
	void rating();
	void get_comments(std::vector<std::string> demand);
	void get_rating(std::vector<std::string>demand);
	void add_rating(std::vector<std::string>demand);
	void get_wallet(std::vector<std::string>request);
	void default_price_filter();
	void avtive_or_deactive_default_filter(std::vector<std::string>demand);
	void manual_weight();
	void manual_weight_handle(std::vector<std::string>demand);
	void manual_off_checks(std::vector<std::string>demand);
	bool manual_checks;
	void set_weights(std::vector<std::string>demand);
	void get_manual(std::vector<std::string>demand);
	void check_rate_value(float ls, float cs, float ss, float fs, float vs);
	void calculate_rating_personal_with_weight(Hotel* check_hotel);
	void calculate_rating_personal_without_weight(Hotel* check_hotel);
	void weight_estimation(Hotel* check_hotel);
	float dif(std::vector<float>score, std::vector<float>weights, int wich, float overral_rat);
	float error_func(std::vector<float>score, std::vector<float>weights, float overral_rat);
	float cal_ave(std::vector<float>score, std::vector<float>weights);
	void gradient_descent(std::vector<float>weights);
	void check_valid_weight();
	void set_weight(std::vector<float>weights);
	void update_weight(std::vector<float>updates_d);
	std::vector<float>base_weight;
	void weight_handle();
	void random_weight();
	Weight* estimated_weight;
	bool insufficient_ratings;
	void get_estimated_weights(std::vector<std::string>demand);
	void update_base_weight();
	void zero_d(std::vector<float>&cal_d);
	void weight_sets();
};


#endif 
