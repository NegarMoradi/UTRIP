#include"User.h"
#include"Header.h"
#include"Reserve.h"
#include"Exceptions.h"
#include"Filter.h"
#include"Hotel.h"

#define ZERO 0
#define ONE 1
#define TWO 2
#define THIRTY 30
#define EMPTY "Empty"
#define OK "OK"
#define STANDARD "standard"
#define DELUXE "deluxe"
#define LUXURY "luxury"
#define PREMIUM "premium"
#define STAR "star"
#define CITY "city"
#define PRICE "price"
#define ROOM "room"

using namespace std;

User::User(std::string email_, std::string name_, std::string pass_)
{
	email = email_;
	user_name = name_;
	hash<string> hash_string;
	password = hash_string(pass_);
	wallet = ZERO;
	bills.push_back(ZERO);
}

bool User::check_valid_email_and_name(string email_, string username_)
{
	if ((email == email_) || (user_name == username_))
		return true;
}
bool User::check_email_and_pass(string email_, string pass_)
{
	hash<string> hash_string;
	string pass;
	pass = hash_string(pass_);
	if ((email == email_) && (password == pass))
		return true;
}
void User::amount(float amount_num)
{
	if (amount_num <= 0)
		throw Bad_request();
	else
	{
		wallet += amount_num;
		bills.push_back(amount_num);
		cout << OK << endl;
	}
}
void User::count(int count_num)
{
	int counter = 0;
	int wallet_num = bills.size() - ONE;
	if (count_num <= bills.size())
	{
		while (counter < count_num)
		{
			cout << bills[wallet_num] << endl;
			wallet_num--;
			counter++;
		}
	}
	else
		count_for_smaller_size();
}
void User::count_for_smaller_size()
{
	int counter = 0;
	int num = bills.size() - ONE;
	while (counter < bills.size())
	{
		cout << bills[num] << endl;
		counter++;
		num--;
	}
}
void User::add_cityflter()
{
	check_filter_exist(CITY);
	CityFilter* new_filter = new CityFilter();
	filters.push_back(new_filter);
}

void User::add_starfilter(string command)
{
	check_filter_exist(STAR);
	StarFilter* new_filter = new StarFilter(command);
	filters.push_back(new_filter);
}

void User::add_pricefilter(string command)
{
	check_filter_exist(PRICE);
	PriceFilter* new_filter = new PriceFilter(command);
	filters.push_back(new_filter);
}
void User::add_roomfilter(string command)
{
	check_filter_exist(ROOM);
	RoomFilter* new_filter = new RoomFilter(command);
	filters.push_back(new_filter);
}
void User::check_filter_exist(string type)
{
	for (int i = 0; i < filters.size(); i++)
		if (filters[i]->return_type() == type)
			filters.erase(filters.begin() + i);
}
void User::print_hotels(vector<Hotel*>hotels)
{
	vector<Hotel*>new_hotels = hotels;
	for (int i = 0; i < filters.size(); i++)
		new_hotels = filters[i]->filter_hotels(new_hotels);
	unique_hotels(new_hotels);
}
void User::unique_hotels(vector<Hotel*>new_hotels)
{
	std::vector <Hotel*> ::iterator it;
	sort(new_hotels.begin(), new_hotels.end(), [](Hotel*& one, Hotel*& second) {
		return one->get_id() < second->get_id();
	});
	it = std::unique(new_hotels.begin(), new_hotels.end(),
		[](Hotel*& a, Hotel*& b) {
		return a->get_id() == b->get_id();;
	});
	new_hotels.resize(std::distance(new_hotels.begin(), it));
	print_new_hotels(new_hotels);
}
void User::print_new_hotels(vector<Hotel*>new_hotels)
{
	sort(new_hotels.begin(), new_hotels.end(), [](Hotel*& one, Hotel*& second) {
		return one->get_id() < second->get_id();
	});
	if (new_hotels.size() > ZERO)
	{
		for (int i = 0; i < new_hotels.size(); i++)
			new_hotels[i]->print();
	}
	else
		cout << EMPTY << endl;
}
void User::delete_filters()
{
	for (int i = 0; i < filters.size(); i++)
		delete filters[i];
	filters.clear();
	cout << OK << endl;
}
void User::add_reserve(Hotel*reserve_hotel, string type, int quantity, int check_in, int check_out)
{
	vector<Room*>reserve_room;
	check_type(type);
	check_credit(reserve_hotel, type,quantity);
	check_in_and_out(check_in, check_out);
	reserve_room = reserve_hotel->room_reserves(type, quantity, check_in, check_out);
	reserve_id = ++next_id;
	Reserve* new_reserve = new Reserve(reserve_id, reserve_hotel, reserve_room, check_in, check_out,type,quantity);
	reserves.push_back(new_reserve);
	wallet -= reserve_hotel->can_pay(type, quantity);
	bills.push_back(wallet);
}
void User::check_type(string type)
{
	bool check = false;
	if ((type == STANDARD) || (type == DELUXE) || (type == LUXURY) || (type == PREMIUM))
		check = true;
	if (check == false)
		throw Bad_request();
}
void User::check_credit(Hotel*reserve_hotel, string type, int quantity)
{
	if (wallet < reserve_hotel->can_pay(type, quantity))
		throw Not_enough_credit();
}
void User::check_in_and_out(int in, int out)
{
	if ((in < ONE) || (out < ONE) || (in > THIRTY) || (out > THIRTY))
		throw Bad_request();
}
void User::print_reserves()
{
	vector<Reserve*>reverse_reserve;
	reverse_reserve = reserves;
	reverse(reverse_reserve.begin(), reverse_reserve.end());
	for (int i = 0; i < reverse_reserve.size(); i++)
		reverse_reserve[i]->print();
}
void User::delete_reserve(int id)
{
	bool check = false;
	for (int i = 0; i < reserves.size(); i++)
		if (reserves[i]->id == id)
		{
			reserves[i]->handle_delete();
			wallet += (reserves[i]->cost / TWO);
			bills.push_back(wallet);
			reserves.erase(reserves.begin() + i);
			check = true;
		}
	if (check == true)
		cout << OK << endl;
	else
		throw Not_found();
}