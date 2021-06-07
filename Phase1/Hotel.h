#ifndef HOTEL_H
#define HOTEL_H "HOTEL_H"

#include "Header.h"

class Score;
class Comment;
class Room;
class Hotel
{
public:
	Hotel(std::string ui, std::string pn, int sr,std::string o, std::string a, std::string c, float lat, float lon, std::string img,
		int ns, int nd, int nl, int np, float sp, float dp, float lp, float pp);
	void print();
	std::string get_id() { return unique_id; }
	bool has_same_name(std::string id);
	void print_one_hotel();
	bool has_same_city(std::string city_name);
	bool filters_by_star(int min_star, int max_star);
	bool filters_by_price(float min_price, float max_price);
	int can_pay(std::string type, int quantity);
	void add_comments(std::string username, std::string comments_);
	void add_score(std::string username_, float ls, float cs, float ss, float fs, float vs, float os);
	void get_score();
	void print_rate(float ls, float cs, float ss, float fs, float vs, float os);
	void get_comments();
	bool filters_by_room(std::string type, int quantity, int check_in_, int check_out_);
	int check_how_may_room_empty(std::string type, int check_in_, int check_out_);
	std::vector<Room*> room_reserves(std::string type,int quantity, int check_in, int check_out);
	std::vector<Room*> return_rooms_reserve(std::string type, int quantity, int check_in, int check_out);
private:
	void add_rooms(int ns, int nd, int nl, int np, float sp, float dp, float lp, float pp);
	void add_standard_room(int num, float price);
	void add_deluxe_room(int num, float price);
	void add_luxury_room(int num, float price);
	void add_premium_room(int num, float price);
	std::string unique_id;
	std::string property_name;
	int star_rating;
	std::string overview;
	std::string amenities;
	std::string city;
	float latitude;
	float longitude;
	std::string image_url;
	int num_of_standard_rooms;
	int num_of_deluxe_rooms;
	int num_of_luxury_rooms;
	int num_of_premium_rooms;
	int total_num_of_rooms;
	float average_price;
	float standard_price;
	float deluxe_price;
	float luxury_price;
	float premium_price;
	std::vector<Room*>rooms;
	std::vector<Comment*>comments;
	std::vector<Score*>scores;
	float calculate_average(float sp, float dp, float lp, float pp);
	std::vector<Room*> add_new_rooms(std::vector<Room*>room, int quantity, int check_in, int check_out);
	bool check_score_exist(std::string username);
	void check_rate_value(float ls, float cs, float ss, float fs, float vs, float os);
	void replace_score(std::string username_, float ls, float cs, float ss, float fs, float vs, float os);
};

#endif 
