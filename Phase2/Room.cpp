#include "Room.hpp"
#include"Header.hpp"

using namespace std;

Room::Room(float price, string room_id)
{
	id = room_id;
	room_price = price;
	reserve = false;
	check_in = ZERO;
	check_out = ZERO;
}

bool Room::check_reserve(int check_in_, int check_out_)
{
	if ((check_in == ZERO)&&(check_out == ZERO))
		return false;
	else
	{
		for (int i = 0; i < reserve_date.size(); i++)
			if (((reserve_date[i][0] <= check_in_) && (check_in_ <= reserve_date[i][1])) || ((check_out_ >= reserve_date[i][0]) && (check_out_ <= reserve_date[i][1])))
			return true;
		return false;
	}
}
void Room::set_checks(int check_in_, int check_out_)
{
	check_in = check_in_;
	check_out = check_out_; 
	vector<int>new_date;
	new_date.push_back(check_in_);
	new_date.push_back(check_out_);
	reserve_date.push_back(new_date);
}
void Room::print_id()
{
	cout << id << SPACE;
}
void Room::delete_reserve(int in, int out)
{
	for (int i = 0; i < reserve_date.size(); i++)
		if ((reserve_date[i][ZERO] == in) && (reserve_date[i][ONE] == out))
			reserve_date.erase(reserve_date.begin() + i);
}
Standard_Room::Standard_Room(float price, int num)
	:Room(price, standard_name+to_string(num+ONE))
{;}

Deluxe_Room::Deluxe_Room(float price, int num)
	:Room(price, deluxury_name+to_string(num + ONE))
{;}

Luxury_Room::Luxury_Room(float price, int num)
	:Room(price, luxury_name+to_string(num + ONE))
{;}

Premium_Room::Premium_Room(float price, int num)
	:Room(price,premium_name+to_string(num + ONE))
{;}