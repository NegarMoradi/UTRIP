#ifndef INPUTS_HPP
#define INPUTS_HPP "INPUTS_HPP"

#include"Header.hpp"
class Hotel;
class Score;

class Input
{
public:
	Input();
	void read_file(std::string file_name, std::vector<Hotel*>&hotels, std::vector<Score*>all_score);
	void read_ratings(std::vector<std::string> name, std::vector<Hotel*>&hotels);
	void set_rating(std::vector<std::string> parts, std::vector<Score*>&all_score);
	void set_hotel_detail(std::vector<std::string> parts, std::vector<Hotel*>&hotels, std::vector<Score*>all_score);
private:
	std::vector<std::string> split(const std::string &s, char delim);
	Score* return_score(std::string name, std::vector<Score*>all_score);
};



#endif 
