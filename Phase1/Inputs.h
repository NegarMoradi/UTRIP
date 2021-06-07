#ifndef INPUTS_H
#define INPUTS_H "INPUTS_H"

#include"Header.h"
class Hotel;

class Input
{
public:
	Input();
	void read_file(std::string file_name, std::vector<Hotel*>&hotels);
	void set_hotel_detail(std::vector<std::string> parts, std::vector<Hotel*>&hotels);
private:
	std::vector<std::string> split(const std::string &s, char delim);
};



#endif 
