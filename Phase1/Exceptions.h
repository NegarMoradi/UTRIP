#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H "EXCEPTIONS_H"

#include<exception>

class Not_found :public std::exception
{
public:
	const char* what() const throw();
};

class Bad_request :public std::exception
{
public:
	const char* what() const throw();
};

class Permission_denied :public std::exception
{
public:
	const char* what() const throw();
};

class Empty :public std::exception
{
public:
	const char* what() const throw();
};

class Not_enough_credit :public std::exception
{
public:
	const char* what() const throw();
};

class Not_enough_room :public std::exception
{
public:
	const char* what() const throw();
};

class No_rating :public std::exception
{
public:
	const char* what() const throw();
};

#endif