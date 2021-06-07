#ifndef COMMENT_H
#define COMMENT_H "COMMENT_H"

#include"Header.h"

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
