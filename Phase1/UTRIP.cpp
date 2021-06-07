#include"UTRIP.h"
#include"User.h"
#include"Header.h"
#include"Inputs.h"
#include"Hotel.h"
#include"Exceptions.h"
#include"Reserve.h"
#include"Comment.h"

#define POST "POST"
#define GET "GET"
#define QUESTION_MARK '?'
#define SIGNUP "signup"
#define LOGIN "login"
#define EMAIL "email"
#define USERNAME "username"
#define PASSWORD "password"
#define OK "OK"
#define LOGOUT "logout"
#define WALLET "wallet"
#define COUNT "count"
#define AMOUNT "amount"
#define HOTELS "hotels"
#define HOTEL "hotel"
#define EMPTY "Empty"
#define ZERO 0
#define TWO 2
#define THREE 3
#define SPACE ' '
#define S_QUESTION_MARK "?"
#define ID "id"
#define FILTERS "filters"
#define CITY "city"
#define MIN_STAR "min_star"
#define MAX_STAR "max_star"
#define MIN_PRICE "min_price"
#define MAX_PRICE "max_price"
#define TYPE "type"
#define QUANTITY "quantity"
#define CHECK_IN "check_in"
#define CHECK_OUT "check_out"
#define DELETE "DELETE"
#define RESERVES "reserves"
#define COMMENTS "comments"
#define COMMENT "comment"
#define RATINGS "ratings"
#define LOCATION "location"
#define	CLEANLINESS "cleanliness"
#define STAFF "staff"
#define FACILITIES "facilities"
#define VALUE_FOR_MONEY "value_for_money"
#define OVERALL_RATING "overall_rating"

using namespace std;

UTRIP::UTRIP(string file_name)
{
	getput->read_file(file_name, hotels);
	main_user = NULL;
}

void UTRIP::get_put()
{
	string command;
	while (cin >> command)
	{
		try
		{
			getting_input(command);
		}
		catch (const std::exception& exception)
		{
			cerr << exception.what();
		}
	}
}

void UTRIP::getting_input(string command)
{
	if (command == POST)
		post_demand();
	else if (command == GET)
		get_demand();
	else if (command == DELETE)
		delete_command();
	else
		throw Bad_request();
}
void UTRIP::post_demand()
{
	string demand;
	cin >> demand;
	if (demand == SIGNUP)
		signup();
	else if (demand == LOGIN)
		login();
	else if (demand == LOGOUT)
		logout();
	else if (demand == WALLET)
		wallet();
	else if (demand == FILTERS)
		filters();
	else if (demand == RESERVES)
		reserves();
	else if (demand == COMMENTS)
		comments();
	else if (demand == RATINGS)
		rating();
	else
		throw Not_found();
}
void UTRIP::get_demand()
{
	string demand;
	cin.ignore();
	getline(cin, demand);
	vector<string> request = split(demand, SPACE);
	check_main_user();
	if (request[ZERO] == HOTELS)
		get_hotels(request);
	else if (request[ZERO] == RESERVES)
		get_reserves();
	else if (request[ZERO] == COMMENTS)
		get_comments(request);
	else if (request[ZERO] == RATINGS)
		get_rating(request);
	else if (request[ZERO] == WALLET)
		get_wallet(request);
	else
		throw Not_found();
}
void UTRIP::check_question_mark()
{
	char question;
	cin >> question;
	if (question != QUESTION_MARK)
	{
		string throw_away;
		getline(cin, throw_away);
		throw Bad_request();
	}
}
void UTRIP::signup()
{
	check_question_mark();
	string email, username, pass, command;
	int counter = 0;
	while (counter < 3)
	{
		cin >> command;
		if (command == EMAIL)
		{
			cin >> email;
			counter++;
		}
		else if (command == USERNAME)
		{
			cin >> username;
			counter++;
		}
		else if (command == PASSWORD)
		{
			cin >> pass;
			counter++;
		}
	}
	check_email_and_username(email, username);
	User* new_user = new User(email, username, pass);
	users.push_back(new_user);
	main_user = new_user;
	cout << OK << endl;
}
void UTRIP::login()
{
	check_question_mark();
	string  email, pass, command;
	int counter = 0;
	while (counter < 2)
	{
		cin >> command;
		if (command == EMAIL)
		{
			cin >> email;
			counter++;
		}
		else if (command == PASSWORD)
		{
			cin >> pass;
			counter++;
		}
	}
	main_user = find_user(email, pass);
	cout << OK << endl;
}

void UTRIP::check_email_and_username(string email_, string username_)
{
	for (int i = 0; i < users.size(); i++)
		if (users[i]->check_valid_email_and_name(email_, username_))
			throw Bad_request();
}
User* UTRIP::find_user(string emai_, string pass_)
{
	for (int i = 0; i < users.size(); i++)
		if (users[i]->check_email_and_pass(emai_, pass_))
			return users[i];
	throw Bad_request();
}

void UTRIP::check_main_user()
{
	if (main_user == NULL)
		throw Permission_denied();
}
void UTRIP::logout()
{
	check_main_user();
	main_user->delete_filters();
	main_user = NULL;
}
void UTRIP::wallet()
{
	check_main_user_for_another();
	check_question_mark();
	string request;
	cin >> request;
	wallet_handle(request);
}
void UTRIP::wallet_handle(string request)
{
	float amount_num;
	if (request == AMOUNT)
	{
		cin >> amount_num;
		main_user->amount(amount_num);
	}
	else
		throw Bad_request();
}
void UTRIP::get_wallet(vector<string>request)
{
	check_main_user();
	if ((request[ONE] == S_QUESTION_MARK) && (request[TWO] == COUNT))
		main_user->count(stoi(request[THREE]));
	else
		throw Bad_request();
}
vector<string>UTRIP:: split(const string &s, char delim) {
	vector<string> result;
	istringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		result.push_back(item);
	}
	return result;
}
void UTRIP::get_hotels(vector<string>demand)
{
	if (demand.size() == ONE)
		print_all_hotels();
	else
	{
		if (demand[ONE] != S_QUESTION_MARK)
			throw Bad_request();
		else
			print_one_hotel(demand);
	}
}
void UTRIP::print_one_hotel(vector<string>id)
{
	if (id[TWO] == ID)
		find_and_print_hotel(id[THREE]);
	else
		throw Bad_request();
}
void UTRIP::find_and_print_hotel(string id)
{
	bool check = false;
	for (int i = 0; i < hotels.size(); i++)
		if (hotels[i]->has_same_name(id) == true)
		{
			hotels[i]->print_one_hotel();
			check = true;
		}
	if (check == false)
		throw Not_found();
}
void UTRIP::print_all_hotels()
{
	if (main_user->filters_size() == ZERO)
	{
		if (hotels.size() == ZERO)
			cout << EMPTY;	
		else
		{
			sort_hotels();
			for (int i = 0; i < hotels.size(); i++)
				hotels[i]->print();
		}
	}
	else
		print_filter_hotels();
}
void UTRIP::print_filter_hotels()
{
	main_user->print_hotels(hotels);
}
void UTRIP::sort_hotels()
{
	sort(hotels.begin(), hotels.end(), [](Hotel*& one, Hotel*& second) {
		return one->get_id() < second->get_id();
	});
}

void UTRIP::filters()
{
	check_main_user_for_another();
	check_question_mark();
	string command;
	cin >> command;
	choose_filter(command);
}
void UTRIP::check_main_user_for_another()
{
	if (main_user == NULL)
	{
		string throw_away;
		getline(cin, throw_away);
		throw Permission_denied();
	}
}
void UTRIP::choose_filter(string command)
{
	if (command == CITY)
		main_user->add_cityflter();
	else if (command == MIN_STAR || command == MAX_STAR)
		main_user->add_starfilter(command);
	else if (command == MIN_PRICE || command == MAX_PRICE)
		main_user->add_pricefilter(command);
	else if (command == TYPE || command == QUANTITY || command == CHECK_IN || command == CHECK_OUT)
		main_user->add_roomfilter(command);
	else
		throw Bad_request();
}
void UTRIP::delete_command()
{
	string request;
	cin >> request;
	check_main_user_for_another();
	if (request == FILTERS)
		main_user->delete_filters();
	else if (request == RESERVES)
		delete_reserve();
	else
		throw Bad_request();
}
void UTRIP::delete_reserve()
{
	check_question_mark();
	string demand;
	int id;
	cin >> demand;
	if (demand == ID)
	{
		cin >> id;
		main_user->delete_reserve(id);
	}
	else
		throw Bad_request();
}
void UTRIP::reserves()
{
	check_main_user_for_another();
	check_question_mark();
	string command;
	cin.ignore();
	getline(cin, command);
	vector<string>split_space = split(command, SPACE);
	get_info_for_reserve(split_space);
}
void UTRIP::get_info_for_reserve(vector<string>command)
{
	string hotel, type;
	int quantity, check_in, check_out;
	for (int i = 0; i < 10; i++)
	{
		if (command[i] == HOTEL)
			hotel = command[i + ONE];
		else if (command[i] == TYPE)
			type = command[i + ONE];
		else if (command[i] == QUANTITY)
			quantity = stoi(command[i + ONE]);
		else if (command[i] == CHECK_IN)
			check_in = stoi(command[i + ONE]);
		else if (command[i] == CHECK_OUT)
			check_out = stoi(command[i + ONE]);
		else
			throw Bad_request();
		i += ONE;
	}
	main_user->add_reserve(find_hotel(hotel), type, quantity, check_in, check_out);
}
Hotel* UTRIP::find_hotel(string id)
{
	for (int i = 0; i < hotels.size(); i++)
		if (hotels[i]->has_same_name(id) == true)
			return hotels[i];
	throw Not_found();
}
void UTRIP::get_reserves()
{
	if (main_user->get_reserves_size() == ZERO)
		cout << EMPTY << endl;
	else
		main_user->print_reserves();
}
void UTRIP::comments()
{
	check_main_user_for_another();
	check_question_mark();
	string command;
	cin.ignore();
	getline(cin, command);
	vector<string>demand = split(command, SPACE);
	add_comment(demand);
}
void UTRIP::add_comment(vector<string>demand)
{
	string hotel, comment;
	for (int i = 0; i < 4; i++)
	{
		if (demand[i] == HOTEL)
			hotel = demand[i + ONE];
		else if (demand[i] == COMMENT)
			comment = demand[i + ONE];
		else
			throw Bad_request();
		i += ONE;
	}
	find_hotel(hotel)->add_comments(main_user->get_username(), comment);
}
void UTRIP::get_comments(vector<string>demand)
{
	if (demand[ONE] != S_QUESTION_MARK)
		throw Bad_request();
	else
	{
		if (demand[TWO] == HOTEL)
			find_hotel(demand[THREE])->get_comments();
		else throw Bad_request();
	}
}
void UTRIP::rating()
{
	check_main_user_for_another();
	check_question_mark();
	string command;
	cin.ignore();
	getline(cin, command);
	vector<string>demand = split(command, SPACE);
	add_rating(demand);
}
void UTRIP::add_rating(vector<string>demand)
{
	string hotel_id;
	float location, cleanliness, staff, facilities, money, overall;
	for (int i = 0; i < demand.size(); i++)
	{
		if (demand[i] == HOTEL)
			hotel_id = demand[i + ONE];
		else if (demand[i] == LOCATION)
			location = stof(demand[i + ONE]);
		else if (demand[i] == CLEANLINESS)
			cleanliness = stof(demand[i + ONE]);
		else if (demand[i] == STAFF)
			staff = stof(demand[i + ONE]);
		else if (demand[i] == FACILITIES)
			facilities = stof(demand[i + ONE]);
		else if (demand[i] == VALUE_FOR_MONEY)
			money = stof(demand[i + ONE]);
		else if (demand[i] == OVERALL_RATING)
			overall = stof(demand[i + ONE]);
		else
			throw Bad_request();
		i += ONE;
	}
	find_hotel(hotel_id)->add_score(main_user->get_username(), location, cleanliness,
		staff, facilities, money, overall);
}
void UTRIP::get_rating(vector<string>demand)
{
	if (demand[ONE] != S_QUESTION_MARK)
		throw Bad_request();
	else
	{
		if (demand[TWO] == HOTEL)
			find_hotel(demand[THREE])->get_score();
		else throw Bad_request();
	}
}