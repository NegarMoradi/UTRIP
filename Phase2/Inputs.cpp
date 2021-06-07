#include "Inputs.hpp"
#include "Header.hpp"
#include "Hotel.hpp"
#include "Score.hpp"

using namespace std;

Input::Input(){}

void Input::read_ratings(vector<string> name,vector<Hotel*>&hotels)
{
	ifstream file;
	file.open(name[1]);
	string throw_away_first_line;
	getline(file, throw_away_first_line);
	string str;
	vector<Score*>all_score;
	while (getline(file, str))
	{
		vector<string> part_of_table = split(str, COMMA);
		set_rating(part_of_table,all_score);
	}
	read_file(name[0],hotels,all_score);
}
void Input::set_rating(vector<string> parts	,vector<Score*>&all_score)
{
	string hotel_name = parts[0];
	float location = stof(parts[1]);
	float cleanliness = stof(parts[2]);
	float staff = stof(parts[3]);
	float facilities = stof(parts[4]);
	float value_of_money = stof(parts[5]);
	float overral_rating = stof(parts[6]);
	Score* new_score = new Score(hotel_name, location, cleanliness, staff, facilities, value_of_money, overral_rating);
	all_score.push_back(new_score);
}
Score* Input::return_score(string name, vector<Score*>all_score)
{
	for (int i = 0; i < all_score.size(); i++)
		if (all_score[i]->name == name)
			return all_score[i];
}
void Input::read_file(string file_name, vector<Hotel*>&hotels,vector<Score*>all_score)
{
	ifstream file;
	file.open(file_name);
	string throw_away_first_line;
	getline(file, throw_away_first_line);
	string str;
	while (getline(file, str))
	{
		vector<string> part_of_table = split(str, COMMA);
		set_hotel_detail(part_of_table, hotels,all_score);
	}
}

void Input::set_hotel_detail(vector<string>parts, vector<Hotel*>&hotels, vector<Score*>all_score)
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
		standard_num, deluxe_num, luxury_num, premium_num, standard_price, deluxe_price, luxury_price, premium_price,return_score(id,all_score));
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