#include"Reserve.hpp"
#include"Header.hpp"
#include "Room.hpp"
#include "Hotel.hpp"

using namespace std;

Reserve::Reserve(int id_, Hotel* hotel, std::vector<Room*>room, int in, int out,string type_,int quantity_)
{
	id = id_;
	reserve_hotel = hotel;
	rooms = room;
	check_in = in;
	check_out = out;
	quantity = quantity_;
	type = type_;
	cost = (quantity_*room[ZERO]->room_price);
}
void Reserve::print()
{
	float cost_ = (floorf(cost * HUNDRED) / HUNDRED);
	cout << ID_ << id << SPACE << HOTEL_ << reserve_hotel->get_id() << SPACE
		<< ROOM_ << type << SPACE << QUANTITY_ << quantity << SPACE;
	cout << COST_ << fixed << setprecision(ZERO) << cost_;
	cout << SPACE << CHECK_IN_ << check_in << SPACE << CHECK_OUT_ << check_out << SPACE << endl;
}
void Reserve::handle_delete()
{
	for (int i = 0; i < rooms.size(); i++)
		rooms[i]->delete_reserve(check_in, check_out);
}