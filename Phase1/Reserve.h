#ifndef RESERVE_H
#define RESERVE_H "RESERVE_H"

#include"Header.h"

class Hotel;
class Room;
class Reserve
{
public:
	Reserve(int id_, Hotel* hotel, std::vector<Room*>room, int in, int out,std::string type_,int quantity_);
	int id;
	float cost;
	void print();
	void handle_delete();
private:
	Hotel* reserve_hotel;
	std::vector<Room*>rooms;
	int check_in;
	int check_out;
	int quantity;
	std::string type;
};

#endif 
