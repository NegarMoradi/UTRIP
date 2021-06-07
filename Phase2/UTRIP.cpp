#include"UTRIP.hpp"
#include"User.hpp"
#include"Header.hpp"
#include"Inputs.hpp"
#include"Hotel.hpp"
#include"Exceptions.hpp"
#include"Reserve.hpp"
#include"Comment.hpp"
#include"Weight.hpp"

using namespace std;

UTRIP::UTRIP(vector<string> file_name)
{
	getput->read_ratings(file_name,hotels);
	main_user = NULL;
	sorting = false;
	manual_checks = false;
	default_budget = true;
	insufficient_ratings = false;
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
	else if (demand == SORT)
		sorting_hotels();
	else if (demand == DEFAULT_PRICE_FILTER)
		default_price_filter();
	else if (demand == MANUAL_WEIGHTS)
		manual_weight();
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
	else if (request[ZERO] == MANUAL_WEIGHTS)
		get_manual(request);
	else if (request[ZERO] == ESTIMATED_WEIGHTS)
		get_estimated_weights(request);
	else
		throw Not_found();
}
void UTRIP::check_question_mark()
{
	char question;
	cin >> question;
	if (question != QUESTION_MARK)
		throw Bad_request();
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
		if (users[i]->check_valid_email_and_name(email_, username_)==true)
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
	check_main_user();
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
	if (insufficient_ratings == true)
		throw Insufficient_Ratings();
	if (main_user->filters_size() == ZERO)
	{
		if (hotels.size() == ZERO)
			cout << EMPTY;	
		else
			check_filter_default_budget();
	}
	else
		print_filter_hotels();
}
void UTRIP::print_without_default_budget()
{
	if (sorting == false)
		sort_hotels();
	for (int i = 0; i < hotels.size(); i++)
		hotels[i]->print();
}
void UTRIP::check_filter_default_budget()
{
	if ((default_budget == true) && (main_user->check_num_of_reserve() == true))
		print_by_default_budget_filter();
	else
		print_without_default_budget();
}
void UTRIP::print_by_default_budget_filter()
{
	main_user->add_default_filter();
	main_user->print_by_default_filter(hotels);
}
void UTRIP::print_filter_hotels()
{
	sort_hotels();
	main_user->print_hotels(hotels);
}
void UTRIP::sort_hotels()
{
	if (sorting == false)
		sort(hotels.begin(), hotels.end(), [](Hotel*& one, Hotel*& second) {
		return one->get_id() < second->get_id();
	});
	else
		return;
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
	main_user->add_score(hotel_id, location, cleanliness, staff, facilities, money, overall);
	main_user->num_of_scores++;
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
void UTRIP::sorting_hotels()
{
	check_main_user_for_another();
	cin.ignore();
	string command;
	getline(cin, command);
	vector<string>demand = split(command, SPACE);
	if (demand.size() != FIVE)
		throw Bad_request();
	if (demand[ZERO] == S_QUESTION_MARK)
	{
		demand.erase(demand.begin() + ZERO);
		sort_checks(demand);
	}
	else
		throw Bad_request();
}
void UTRIP::sort_checks(vector<string>demand)
{
	string property_value, order;
	for (int i = 0; i < 4; i++)
	{
		if (demand[i] == PROPERTY)
			property_value = demand[i + ONE];
		else if (demand[i] == ORDER)
			order = demand[i + ONE];
		i += ONE;
	}
	check_order(order);
	check_property(property_value);
	sort_handling(property_value, order);
}
void UTRIP::check_order(string value)
{
	bool check = false;
	if ((value == ASCENDING) || (value == DESCENDING))
		check = true;
	if(check==false)
		throw Bad_request();
}
void UTRIP::check_property(string value)
{
	bool check = false;
	if ((value == ID) || (value == NAME) || (value == CITY) || (value == STAR_RATING) || (value == STANDARD_ROOM_PRICE)
		|| (value == DELUXE_ROOM_PRICE) || (value == PREMIUM_ROOM_PRICE) || (value == LUXURY_ROOM_PRICE) || (value == AVERAGE_ROOM_PRICE) ||
		(value == RATING_OVERALL) || (value == RATING_PERSONAL))
		check = true;
	if (check == false)
		throw Bad_request();
}
bool compare_id(Hotel*& one, Hotel*& second)
{
	return  one->get_id() < second->get_id();
}
void UTRIP::sort_handling(string property, string order)
{
	sorting = true;
	if (property == ID)
		sort_hotels_by_id(order);
	else if (property == NAME)
		sort_hotels_by_name(order);
	else if (property == STAR_RATING)
		sort_hotels_by_star_rating(order);
	else if (property == CITY)
		sort_hotels_by_city(order);
	else if (property == STANDARD_ROOM_PRICE)
		sort_hotels_by_sp(order);
	else if (property == DELUXE_ROOM_PRICE)
		sort_hotels_by_dp(order);
	else if (property == LUXURY_ROOM_PRICE)
		sort_hotels_by_lp(order);
	else if (property == PREMIUM_ROOM_PRICE)
		sort_hotels_by_pp(order);
	else if (property == AVERAGE_ROOM_PRICE)
		sort_hotels_by_ap(order);
	else if (property == RATING_OVERALL)
		sort_hotels_by_ro(order);
	else if (property == RATING_PERSONAL)
		sort_hotels_by_rp(order);
	else
		throw Bad_request();
}
void UTRIP::sort_hotels_by_id(string order)
{
	if (order == ASCENDING)
		sort(hotels.begin(), hotels.end(), compare_id);
	else if (order == DESCENDING)
	{
		sort(hotels.begin(), hotels.end(), compare_id);
		std::reverse(hotels.begin(), hotels.end());
	}
	cout << OK << endl;
}
bool compare_name(Hotel*& one, Hotel*& second)
{
	if(one->get_name() == second->get_name())
		return  one->get_id() < second->get_id();
	else
		return one->get_name() < second->get_name();
}
void UTRIP::sort_hotels_by_name(string order)
{
	if (order == ASCENDING)
		sort(hotels.begin(), hotels.end(), compare_name);
	else if (order == DESCENDING)
	{
		sort(hotels.begin(), hotels.end(), compare_name);
		std::reverse(hotels.begin(), hotels.end());
	}
	cout << OK << endl;
}
bool compare_sr(Hotel*& one, Hotel*& second)
{
	if (one->get_sr() == second->get_sr())
		return  one->get_id() < second->get_id();
	else
		return one->get_sr() < second->get_sr();
}
void UTRIP::sort_hotels_by_star_rating(string order)
{
	if (order == ASCENDING)
		sort(hotels.begin(), hotels.end(), compare_sr);
	else if (order == DESCENDING)
	{
		sort(hotels.begin(), hotels.end(), compare_sr);
		std::reverse(hotels.begin(), hotels.end());
	}
	cout << OK << endl;
}
bool compare_city(Hotel*& one, Hotel*& second)
{
	if (one->get_city() == second->get_city())
		return  one->get_id() < second->get_id();
	else
		return one->get_city() < second->get_city();
}
void UTRIP::sort_hotels_by_city(string order)
{
	if (order == ASCENDING)
		sort(hotels.begin(), hotels.end(), compare_city);
	else if (order == DESCENDING)
	{
		sort(hotels.begin(), hotels.end(), compare_city);
		std::reverse(hotels.begin(), hotels.end());
	}
	cout << OK << endl;
}
bool compare_sp(Hotel*& one, Hotel*& second)
{
	if (one->get_sp() == second->get_sp())
		return  one->get_id() < second->get_id();
	else
		return one->get_sp() < second->get_sp();
}
void UTRIP::sort_hotels_by_sp(string order)
{
	if (order == ASCENDING)
		sort(hotels.begin(), hotels.end(), compare_sp);
	else if (order == DESCENDING)
	{
		sort(hotels.begin(), hotels.end(), compare_sp);
		std::reverse(hotels.begin(), hotels.end());
	}
	cout << OK << endl;
}
bool compare_dp(Hotel*& one, Hotel*& second)
{
	if (one->get_dp() == second->get_dp())
		return  one->get_id() < second->get_id();
	else
		return one->get_dp() < second->get_dp();
}
void UTRIP::sort_hotels_by_dp(string order)
{
	if (order == ASCENDING)
		sort(hotels.begin(), hotels.end(), compare_dp);
	else if (order == DESCENDING)
	{
		sort(hotels.begin(), hotels.end(), compare_dp);
		std::reverse(hotels.begin(), hotels.end());
	}
	cout << OK << endl;
}
bool compare_lp(Hotel*& one, Hotel*& second)
{
	if (one->get_lp() == second->get_lp())
		return  one->get_id() < second->get_id();
	else
		return one->get_lp() < second->get_lp();
}
void UTRIP::sort_hotels_by_lp(string order)
{
	if (order == ASCENDING)
		sort(hotels.begin(), hotels.end(), compare_sp);
	else if (order == DESCENDING)
	{
		sort(hotels.begin(), hotels.end(), compare_sp);
		std::reverse(hotels.begin(), hotels.end());
	}
	cout << OK << endl;
}
bool compare_pp(Hotel*& one, Hotel*& second)
{
	if (one->get_pp() == second->get_pp())
		return  one->get_id() < second->get_id();
	else
		return one->get_pp() < second->get_pp();
}
void UTRIP::sort_hotels_by_pp(string order)
{
	if (order == ASCENDING)
		sort(hotels.begin(), hotels.end(), compare_pp);
	else if (order == DESCENDING)
	{
		sort(hotels.begin(), hotels.end(), compare_pp);
		std::reverse(hotels.begin(), hotels.end());
	}
	cout << OK << endl;
}
bool compare_ap(Hotel*& one, Hotel*& second)
{
	if (one->get_ap() == second->get_ap())
		return  one->get_id() < second->get_id();
	else
		return one->get_ap() < second->get_ap();
}
void UTRIP::sort_hotels_by_ap(string order)
{
	if (order == ASCENDING)
		sort(hotels.begin(), hotels.end(), compare_ap);
	else if (order == DESCENDING)
	{
		sort(hotels.begin(), hotels.end(), compare_ap);
		std::reverse(hotels.begin(), hotels.end());
	}
	cout << OK << endl;
}
bool compare_ro(Hotel*& one, Hotel*& second)
{
	if (one->get_rating_overall() == second->get_rating_overall())
		return  one->get_id() < second->get_id();
	else
		return one->get_rating_overall() < second->get_rating_overall();
}
void UTRIP::sort_hotels_by_ro(string order)
{
	if (order == ASCENDING)
		sort(hotels.begin(), hotels.end(), compare_ro);
	else if (order == DESCENDING)
	{
		sort(hotels.begin(), hotels.end(), compare_ro);
		std::reverse(hotels.begin(), hotels.end());
	}
	cout << OK << endl;
}
bool compare_rp(Hotel*& one, Hotel*& second)
{
	if (one->rating_personal == second->rating_personal)
		return one->get_id() < second->get_id();
	else
		return one->rating_personal < second->rating_personal;
}
void UTRIP::sort_hotels_by_rp(string order)
{
	set_rating_personal();
	if (order == ASCENDING)
		sort(hotels.begin(), hotels.end(), compare_rp);
	else if (order == DESCENDING)
	{
		sort(hotels.begin(), hotels.end(), compare_rp);
		std::reverse(hotels.begin(), hotels.end());
	}
	cout << OK << endl;
}
void UTRIP::set_rating_personal()
{
	weight_sets();
	for (int i = 0; i < hotels.size(); i++)
	{
		if (hotels[i]->user_rated(main_user->get_username()) == false)
		{
			if (manual_checks == true)
				calculate_rating_personal_with_weight(hotels[i]);
			else
				calculate_rating_personal_without_weight(hotels[i]);
		}
	}
}
void UTRIP::weight_sets() 
{
	if (manual_checks == false)
	{
		random_weight();
		gradient_descent(base_weight);
		check_valid_weight();
		weight_handle();
	}
}
void UTRIP::calculate_rating_personal_with_weight(Hotel* check_hotel)
{
	float location, cleanliness, staff, facilities, money;
	location = main_user->return_weight()->location;
	cleanliness = main_user->return_weight()->cleanliness;
	staff = main_user->return_weight()->staff;
	facilities = main_user->return_weight()->facilities;
	money = main_user->return_weight()->value_of_money;
	check_hotel->set_pr_by_manual_weight(location, cleanliness, staff, facilities, money);
}
void UTRIP::default_price_filter()
{
	check_main_user_for_another();
	string command;
	cin.ignore();
	getline(cin, command);
	vector<string>demand = split(command, SPACE);
	if (demand.size() != THREE)
		throw Bad_request();
	else
	{
		if (demand[ZERO] == S_QUESTION_MARK)
		{
			demand.erase(demand.begin() + ZERO);
			avtive_or_deactive_default_filter(demand);
		}
		else
			throw Bad_request();
	}
}
void UTRIP::avtive_or_deactive_default_filter(vector<string>demand)
{
	if (demand[ZERO] == ACTIVE)
	{
		if (demand[ONE] == TRUE)
			default_budget = true;
		else if (demand[ONE] == FALSE)
			default_budget = false;
		else
			throw Bad_request();
	}
	else
		throw Bad_request(); 
	cout << OK << endl;
}
void UTRIP::manual_weight()
{
	check_main_user_for_another();
	check_question_mark();
	string command;
	cin.ignore();
	getline(cin, command);
	vector<string>demand = split(command, SPACE);
	if (demand.size() == TWELVE)
		manual_weight_handle(demand);
	else if (demand.size() == TWO)
		manual_off_checks(demand);
	else
		throw Bad_request();
		
}
void UTRIP::manual_weight_handle(vector<string>demand)
{
	if ((demand[ZERO] == ACTIVE) && (demand[ONE] == TRUE))
	{
		demand.erase(demand.begin(), demand.begin() + TWO);
		set_weights(demand);
	}
	else
		throw Bad_request();
}
void UTRIP::manual_off_checks(vector<string>demand)
{
	if ((demand[ZERO] == ACTIVE) && (demand[ONE] == FALSE))
	{
		manual_checks = false;
		cout << OK << endl;
	}
	else
		throw Bad_request();
}
void UTRIP::set_weights(vector<string>demand)
{
	float location, cleanliness, staff, facilities, money;
	for (int i = 0; i < demand.size(); i++)
	{
		if (demand[i] == LOCATION)
			location = stof(demand[i + ONE]);
		else if (demand[i] == CLEANLINESS)
			cleanliness = stof(demand[i + ONE]);
		else if (demand[i] == STAFF)
			staff = stof(demand[i + ONE]);
		else if (demand[i] == FACILITIES)
			facilities = stof(demand[i + ONE]);
		else if (demand[i] == VALUE_FOR_MONEY)
			money = stof(demand[i + ONE]);
		else
			throw Bad_request();
		i += ONE;
	}
	check_rate_value(location, cleanliness, staff, facilities, money);
	manual_checks = true;
	main_user->set_weight(location, cleanliness, staff, facilities, money);
}
void UTRIP::check_rate_value(float ls, float cs, float ss, float fs, float vs)
{
	if ((ls < ONE) || (cs < ONE) || (ss < ONE) || (fs < ONE) || (vs < ONE) ||
		(ls > FIVE) || (cs > FIVE) || (ss > FIVE) || (fs > FIVE) || (vs > FIVE))
		throw Bad_request();
}
void UTRIP::get_manual(vector<string>demand)
{
	check_main_user();
	if (demand.size() != ONE)
		throw Bad_request();
	else
		main_user->get_weight(manual_checks);
}
void UTRIP::calculate_rating_personal_without_weight(Hotel* check_hotel)
{
	if (main_user->num_of_scores < FIVE)
		insufficient_ratings=true;
	else
	{
		weight_estimation(check_hotel);
		insufficient_ratings = false;
	}
}
void UTRIP::weight_estimation(Hotel* check_hotel)
{
	float ls = estimated_weight->location;
	float cs = estimated_weight->cleanliness;
	float ss = estimated_weight->staff;
	float fs = estimated_weight->facilities;
	float vs = estimated_weight->value_of_money;
	check_hotel->set_pr_by_manual_weight(ls, cs, ss, fs, vs);
}

float UTRIP::dif(vector<float>score, vector<float>weights, int wich, float overral_rat)
{
	vector<float>new_weight = weights;
	for (int i = 0; i < FIVE; i++)
		if (i == wich)
			new_weight[i] = weights[i] + EPSILON;
	float dif = ((error_func(score, new_weight, overral_rat) - error_func(score, weights, overral_rat)) / EPSILON);
	return dif;
}
float UTRIP::error_func(vector<float>score, vector<float>weights, float overral_rat)
{
	float e_func = cal_ave(score, weights) - overral_rat;
	return pow(e_func, TWO);
}
float UTRIP::cal_ave(vector<float>score, vector<float>weights)
{
	float sum = ZERO;
	float sum_weight = ZERO;
	for (int i = 0; i < FIVE; i++)
		sum += (score[i] * weights[i]);
	for (int j = 0; j < FIVE; j++)
		sum_weight += weights[j];
	return (sum / sum_weight);
}
vector<float>to_vector_score(Score*score)
{
	vector<float>score_;
	score_.push_back(score->location);
	score_.push_back(score->cleanliness);
	score_.push_back(score->staff);
	score_.push_back(score->facilities);
	score_.push_back(score->value_of_money);
	return score_;
}
void UTRIP::gradient_descent(vector<float>weights)
{
	float step = ZERO;
	float step_size = 0.01;
	float step_tolerance = 0.00001;
	vector<Score*>user_score = main_user->get_scores();
	vector<float>new_weight = weights;
	for (int k = 0; k < user_score.size(); k++)
		for (int i = 0; i < 1000; i++)
		{
			for (int j = 0; j < FIVE; j++)
			{
				step = step_size*dif(to_vector_score(user_score[k]), new_weight, j, user_score[k]->overral_rating);
				new_weight[j] -= step;
			}
			if (abs(step) <= step_tolerance)
				break;
		}
	set_weight(new_weight);
}
void UTRIP::set_weight(vector<float>weights)
{
	Weight* new_weight = new Weight(weights[ZERO], weights[ONE], weights[TWO], weights[THREE], weights[FOUR]);
	estimated_weight = new_weight;
	base_weight = weights;
}
void UTRIP::check_valid_weight()
{
	if (estimated_weight->location < ONE)
		estimated_weight->location = ONE;
	else if (estimated_weight->location > FIVE)
		estimated_weight->location = FIVE;
	if (estimated_weight->cleanliness < ONE)
		estimated_weight->cleanliness = ONE;
	else if (estimated_weight->cleanliness > FIVE)
		estimated_weight->cleanliness = FIVE;
	if (estimated_weight->staff < ONE)
		estimated_weight->staff = ONE;
	else if (estimated_weight->staff > FIVE)
		estimated_weight->staff = FIVE;
	if (estimated_weight->facilities < ONE)
		estimated_weight->facilities = ONE;
	else if (estimated_weight->facilities > FIVE)
		estimated_weight->facilities = FIVE;
	if (estimated_weight->value_of_money < ONE)
		estimated_weight->value_of_money = ONE;
	else if (estimated_weight->value_of_money > FIVE)
		estimated_weight->value_of_money = FIVE;
	update_base_weight();
}
void UTRIP::update_base_weight()
{
	base_weight[0] = estimated_weight->location;
	base_weight[1] = estimated_weight->cleanliness;
	base_weight[2] = estimated_weight->staff;
	base_weight[3] = estimated_weight->facilities;
	base_weight[4] = estimated_weight->value_of_money;
}
void UTRIP::weight_handle()
{
	vector<Score*>user_score = main_user->get_scores();
	vector<float>cal_d;
	for (int k = 0; k < FIVE; k++)
		cal_d.push_back(ZERO);
	for (int u = 0; u < THOUSAND; u++)
	{
		zero_d(cal_d);
		for (int i = 0; i < user_score.size(); i++)
			for (int j = 0; j < FIVE; j++)
				cal_d[j] += dif(to_vector_score(user_score[i]), base_weight, j, user_score[i]->overral_rating);
		update_weight(cal_d);
	}
}
void UTRIP::zero_d(vector<float> &cal_d)
{
	for (int l = 0; l < FIVE; l++)
		cal_d[l] = ZERO;
}
void UTRIP::update_weight(vector<float>updates_d)
{
	estimated_weight->location = estimated_weight->location - updates_d[ZERO];
	estimated_weight->cleanliness = estimated_weight->cleanliness - updates_d[ONE];
	estimated_weight->staff = estimated_weight->staff - updates_d[TWO];
	estimated_weight->facilities = estimated_weight->facilities - updates_d[THREE];
	estimated_weight->value_of_money = estimated_weight->value_of_money - updates_d[FOUR];
	check_valid_weight();
}
void UTRIP::random_weight()
{
	srand((unsigned)time(0));
	float random_number;
	for (int i = 0; i < FIVE; i++)
	{
		random_number = (rand() % FIVE) + ONE;
		base_weight.push_back(random_number);
	}
}
void UTRIP::get_estimated_weights(vector<string>demand)
{
	if (demand.size() != ONE)
		throw Bad_request();
	check_main_user();
	estimated_weight->print_for_estimated();
}