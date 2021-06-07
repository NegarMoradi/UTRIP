#ifndef ROOM_H
#define ROOM_H "ROOM_H"
#include"Header.h"

#define STANDARD "standard"
#define DELUXE "deluxe"
#define LUXURY "luxury"
#define PREMIUM "premium"
#define ZERO 0

class Room
{
public:
	Room(float price, std::string room_id);
	virtual std::string return_type() = ZERO;
	std::string id;
	float room_price;
	bool reserve;
	bool check_reserve(int check_in_, int check_out_);
	void set_checks(int check_in_, int check_out_);
	void print_id();
	void delete_reserve(int in, int out);
protected:
	std::vector<std::vector<int>>reserve_date;
	int check_in;
	int check_out;

};

class Standard_Room :public Room
{
public:
	std::string return_type() { return STANDARD; }
	Standard_Room(float price,int num);
};
class Deluxe_Room :public Room
{
public:
	std::string return_type() { return DELUXE; }
	Deluxe_Room(float price, int num);
};
class Luxury_Room :public Room
{
public:
	std::string return_type() { return LUXURY; }
	Luxury_Room(float price, int num);
};
class Premium_Room :public Room
{
public:
	std::string return_type() { return PREMIUM; }
	Premium_Room(float price, int num);
};

#endif 
