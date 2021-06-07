#include"Comment.h"
#include"Header.h"

#define COLON ": "
using namespace std;

Comment::Comment(string username_, string comments_)
{
	username = username_;
	comments = comments_;
}
void Comment::print()
{
	cout << username << COLON << comments << endl;
}