#ifndef UTRIP_H 
#define UTRIP_H "UTRIP_H"

#include"Header.h"
class Hotel;
class Input;
class User;
class Post;
class Get;
class Request;

class UTRIP
{
public:
	UTRIP(std::string file_name);
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
	void add_rating(std::vector<std::string>demand);
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
	void delete_reserve();
	void rating();
	void get_comments(std::vector<std::string> demand);
	void get_rating(std::vector<std::string>demand);
	void get_wallet(std::vector<std::string>request);
};


#endif 
