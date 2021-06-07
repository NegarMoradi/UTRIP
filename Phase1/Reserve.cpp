#include"Reserve.h"
#include"Header.h"
#include "Room.h"
#include "Hotel.h"

#define ZERO 0
#define ID "id: "
#define HOTEL "hotel: "
#define ROOM "room: "
#define QUANTITY "quantity: "
#define COST "cost: "
#define CHECK_IN "check_in "
#define CHECK_OUT "check_out "
#define SPACE ' '

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
	cout << ID << id << SPACE << HOTEL << reserve_hotel->get_id() << SPACE
		<< ROOM << type << SPACE << QUANTITY << quantity << SPACE;
	cout << COST << fixed << setprecision(ZERO) << cost;
	cout << SPACE << CHECK_IN << check_in << SPACE << CHECK_OUT << check_out << SPACE << endl;
}
void Reserve::handle_delete()
{
	for (int i = 0; i < rooms.size(); i++)
		rooms[i]->delete_reserve(check_in, check_out);
}