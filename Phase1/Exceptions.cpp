#include"Exceptions.h"
using namespace std;

const char* Not_found::what() const throw() { return "Not Found\n"; }

const char* Bad_request::what() const throw() { return "Bad Request\n"; }

const char* Permission_denied::what() const throw() { return "Permission Denied\n"; }

const char* Empty::what() const throw() { return "Empty\n"; }

const char* Not_enough_room::what() const throw() { return "Not Enough Room\n"; }

const char* Not_enough_credit::what() const throw() { return "Not Enough Credit\n"; }

const char* No_rating::what() const throw() { return "No Rating\n"; }