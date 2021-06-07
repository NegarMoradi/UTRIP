#ifndef RESERVE_HPP
#define RESERVE_HPP "RESERVE_HPP"

#include"Header.hpp"

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
	std::vector<Room*>rooms;
private:
	Hotel* reserve_hotel;
	int check_in;
	int check_out;
	int quantity;
	std::string type;
};

#endif 
