#include"Comment.hpp"

#define COLON_ ": "

using namespace std;

Comment::Comment(string username_, string comments_)
{
	username = username_;
	comments = comments_;
}
void Comment::print()
{
	cout << username << COLON_ << comments << endl;
}