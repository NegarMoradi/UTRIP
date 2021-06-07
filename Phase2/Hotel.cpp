#include "Hotel.hpp"
#include "Header.hpp"
#include"Exceptions.hpp"
#include "Room.hpp"
#include"Comment.hpp"
#include"Score.hpp"
#include"Weight.hpp"

using namespace std;

Hotel::Hotel(string ui, string pn, int sr, std::string o, std::string a, string c, float lat, float lon, string img,
	int ns, int nd, int nl, int np, float sp, float dp, float lp, float pp, Score* new_score)
{
	unique_id = ui;
	property_name = pn;
	star_rating = sr;
	city = c;
	latitude = lat;
	longitude = lon;
	image_url = img;
	overview = o;
	amenities = a;
	num_of_standard_rooms = ns;
	num_of_deluxe_rooms = nd;
	num_of_luxury_rooms = nl;
	num_of_premium_rooms = np;
	total_num_of_rooms = ns + nd + nl + np;
	standard_price = sp;
	deluxe_price = dp;
	luxury_price = lp;
	premium_price = pp;
	hotel_score = new_score;
	average_price = calculate_average(sp, dp, lp, pp);
	add_rooms(ns, nd, nl, np, sp, dp, lp, pp);
}

float Hotel::calculate_average(float sp, float dp, float lp, float pp)
{
	int count = FOUR;
	if (sp == ZERO)
		count--;
	if (dp == ZERO)
		count--;
	if (lp == ZERO)
		count--;
	if (pp == ZERO)
		count--;
	if (count == ZERO)
		return ZERO;
	else
		return (sp + dp + lp + pp) / count;
}

void Hotel::add_rooms(int ns, int nd, int nl, int np, float sp, float dp, float lp, float pp)
{
	add_standard_room(ns,sp);
	add_deluxe_room(nd,dp);
	add_luxury_room(nl,lp);
	add_premium_room(np,pp);
}
void Hotel::add_standard_room(int num, float price)
{
	for (int i = 0; i < num; i++)
	{
		Standard_Room* new_room = new Standard_Room(price,i);
		rooms.push_back(new_room);
	}
}
void Hotel::add_deluxe_room(int num, float price)
{
	for (int i = 0; i < num; i++)
	{
		Deluxe_Room* new_room = new Deluxe_Room(price,i);
		rooms.push_back(new_room);
	}
}
void Hotel::add_luxury_room(int num, float price)
{
	for (int i = 0; i < num; i++)
	{
		Luxury_Room* new_room = new Luxury_Room(price,i);
		rooms.push_back(new_room);
	}
}
void Hotel::add_premium_room(int num, float price)
{
	for (int i = 0; i < num; i++)
	{
		Premium_Room* new_room = new Premium_Room(price,i);
		rooms.push_back(new_room);
	}
}

void Hotel::print()
{
	float av = floor(average_price*HUNDRED) / HUNDRED;
	cout << unique_id << SPACE << property_name << SPACE <<
		star_rating << SPACE << city << SPACE << total_num_of_rooms << SPACE;
	cout << fixed << setprecision(TWO) << av << endl;
}
bool Hotel::has_same_name(string id)
{
	if (id == unique_id)
		return true;
}
void Hotel::print_one_hotel()
{
	float lat = floor(latitude * HUNDRED) / HUNDRED;
	float lon = floor(longitude * HUNDRED) / HUNDRED;
	float sp = floor(standard_price * HUNDRED) / HUNDRED;
	float dp = floor(deluxe_price * HUNDRED) / HUNDRED;
	float lp = floor(luxury_price * HUNDRED) / HUNDRED;
	float pp = floor(premium_price * HUNDRED) / HUNDRED;
	cout << unique_id << endl;
	cout << property_name << endl;
	cout << STAR_ << star_rating << endl;
	cout << OVERVIEW_ << overview << endl;
	cout << AMENITIES_ << amenities << endl;
	cout << CITY_ << city << endl;
	cout << LATITUDE_ << fixed << setprecision(TWO) << lat << endl;
	cout << LONGITUDE_ << fixed << setprecision(TWO) << lon << endl;
	cout << ROOMS__ << num_of_standard_rooms << SPACE << num_of_deluxe_rooms << SPACE << num_of_luxury_rooms << SPACE << num_of_premium_rooms << endl;
	cout << PRICE_ << fixed << setprecision(ZERO) << sp << SPACE << dp << SPACE << lp << SPACE << pp << endl;
}

bool Hotel::has_same_city(string city_name)
{
	if (city == city_name)
		return true;
	return false;
}
bool Hotel::filters_by_star(int min_star, int max_star)
{
	if ((min_star <= star_rating) && (max_star >= star_rating))
		return true;
	return false;
}

bool Hotel::filters_by_price(float min_price, float max_price)
{
	if ((average_price >= min_price) && (average_price <= max_price))
		return true;
	return false;
}
bool Hotel::filters_by_room(string type, int quantity, int check_in_, int check_out_)
{
	if (check_how_may_room_empty(type, check_in_, check_out_) >= quantity)
		return true;
	return false;
}
int Hotel::check_how_may_room_empty(string type,int check_in_,int check_out_)
{
	int counter = ZERO;
	for (int i = 0; i < rooms.size(); i++)
		if ((rooms[i]->return_type() == type) && (rooms[i]->check_reserve(check_in_, check_out_) == false))
			counter++;
	return counter;
}
vector<Room*> Hotel::room_reserves(string type,int quantity, int check_in, int check_out)
{
	if (filters_by_room(type, quantity, check_in, check_out) == false)
		throw Not_enough_room();
	else
		return return_rooms_reserve(type, quantity, check_in, check_out);
}
vector<Room*> Hotel::return_rooms_reserve(string type, int quantity, int check_in, int check_out)
{
	vector<Room*>new_rooms;
	for (int i = 0; i < rooms.size(); i++)
		if ((rooms[i]->return_type() == type) && (rooms[i]->check_reserve(check_in, check_out) == false))
			new_rooms.push_back(rooms[i]);
	return add_new_rooms(new_rooms, quantity,check_in,check_out);
}
vector<Room*> Hotel::add_new_rooms(vector<Room*>room, int quantity, int check_in, int check_out)
{
	vector<Room*>return_rooms;
	for (int i = 0; i < quantity; i++)
	{
		return_rooms.push_back(room[i]);
		room[i]->set_checks(check_in, check_out);
		room[i]->print_id();
	}
	cout << endl;
	return return_rooms;
}
int Hotel::can_pay(string type, int quantity)
{
	if (type == STANDARD)
		return (standard_price*quantity);
	else if (type == DELUXE)
		return (deluxe_price*quantity);
	else if (type == LUXURY)
		return (luxury_price*quantity);
	else if (type == PREMIUM)
		return (premium_price*quantity);
}
void Hotel::add_comments(string username, string comments_)
{
	Comment* new_comment = new Comment(username, comments_);
	comments.push_back(new_comment);
	cout << OK << endl;
}
void Hotel::get_comments()
{
	for (int i = 0; i < comments.size(); i++)
		comments[i]->print();
}
void Hotel::add_score(string username_, float ls, float cs, float ss, float fs, float vs, float os)
{
	check_rate_value(ls, cs, ss, fs, vs, os);
	if (check_score_exist(username_) == true)
		replace_score(username_, ls, cs, ss, fs, vs, os);
	else
	{
		Score* new_rate = new Score(ls, cs, ss, fs, vs, os, username_);
		scores.push_back(new_rate);
		cout << OK << endl;
	}
}
void Hotel::check_rate_value(float ls, float cs, float ss, float fs, float vs, float os)
{
	if ((ls < ONE) || (cs < ONE) || (ss < ONE) || (fs < ONE) || (vs < ONE) || (os < ONE) ||
		(ls > FIVE) || (cs > FIVE) || (ss > FIVE) || (fs > FIVE) || (vs > FIVE) || (os > FIVE))
		throw Bad_request();
}
void Hotel::get_score()
{
	hotel_score->print();
}
bool Hotel::check_score_exist(string username)
{
	for (int i = 0; i < scores.size(); i++)
		if (scores[i]->username == username)
			return true;
	return false;
}
void Hotel::replace_score(string username_, float ls, float cs, float ss, float fs, float vs, float os)
{
	for (int i = 0; i < scores.size(); i++)
		if (scores[i]->username == username_)
		{
			scores[i]->location = ls;
			scores[i]->cleanliness = cs;
			scores[i]->staff = ss;
			scores[i]->facilities = fs;
			scores[i]->value_of_money = vs;
			scores[i]->overral_rating = os;
		}
}
bool Hotel::check_default_budget(float average, float deviation)
{
	float abs_two_ave = abs(average_price - average);
	if (abs_two_ave <= (TWO*deviation))
		return true;
	return false;
}
bool Hotel::user_rated(string user_name)
{
	if (scores.size() == ZERO)
		return false;
	for (int i = 0; i < scores.size(); i++)
		if (scores[i]->username == user_name)
		{
			rating_personal = scores[i]->overral_rating;
			return true;
		}
	return false;
}
void Hotel::set_pr_by_manual_weight(float ls, float cs, float ss, float fs, float vs)
{
	float sum = ZERO;
	sum += (ls*hotel_score->location);
	sum += (cs*hotel_score->cleanliness);
	sum += (ss*hotel_score->staff);
	sum += (fs*hotel_score->facilities);
	sum += (vs*hotel_score->value_of_money);
	sum = (sum / (ls + cs + ss + fs + vs));
	rating_personal = sum;
}
