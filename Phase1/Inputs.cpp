#include "Inputs.h"
#include "Header.h"
#include "Hotel.h"

#define COMMA ','
using namespace std;

Input::Input(){}

void Input::read_file(string file_name, vector<Hotel*>&hotels)
{
	ifstream file;
	file.open(file_name);
	string throw_away_first_line;
	getline(file, throw_away_first_line);
	string str;
	while (getline(file, str))
	{
		vector<string> part_of_table = split(str, COMMA);
		set_hotel_detail(part_of_table, hotels);
	}
}

void Input::set_hotel_detail(vector<string>parts, vector<Hotel*>&hotels)
{
	string id = parts[0];
	string name = parts[1];
	int star = stoi(parts[2]);
	string overview = parts[3];
	string amenities = parts[4];
	string city = parts[5];
	float latitude = stof(parts[6]);
	float longitude = stof(parts[7]);
	string image = parts[8];
	int standard_num = stoi(parts[9]);
	int deluxe_num = stoi(parts[10]);
	int luxury_num = stoi(parts[11]);
	int premium_num = stoi(parts[12]);
	float standard_price = stof(parts[13]);
	float deluxe_price = stof(parts[14]);
	float luxury_price = stof(parts[15]);
	float premium_price = stof(parts[16]);
	Hotel* new_hotel = new Hotel(id, name, star,overview, amenities, city, latitude, longitude, image,
		standard_num, deluxe_num, luxury_num, premium_num, standard_price, deluxe_price, luxury_price, premium_price);
	hotels.push_back(new_hotel);
}
vector<string> Input::split(const string &s, char delim) {
	vector<string> result;
	istringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		result.push_back(item);
	}
	return result;
}