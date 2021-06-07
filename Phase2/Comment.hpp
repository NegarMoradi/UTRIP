#ifndef COMMENT_HPP
#define COMMENT_HPP "COMMENT_HPP"

#include"Header.hpp"

class Comment
{
public:
	Comment(std::string username_, std::string commnets_);
	void print();
private:
	std::string username;
	std::string comments;
};


#endif 
