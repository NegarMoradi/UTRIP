#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <math.h>
#include <algorithm>
#include <functional>

#define TWO 2
#define ONE 1
#define LOCATION "location"
#define	CLEANLINESS "cleanliness"
#define STAFF "staff"
#define FACILITIES "facilities"
#define VALUE_FOR_MONEY "value_for_money"
#define ACTIVE "active"
#define SPACE ' '
#define TRUE  "true"
#define FALSE "false"
#define HUNDRED 100
#define COMMA ','
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
#define SORT "sort"
#define ZERO 0
#define TWO 2
#define THREE 3
#define FIVE 5
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
#define OVERALL_RATING "overall_rating"
#define PROPERTY "property"
#define ORDER "order"
#define ASCENDING "ascending"
#define DESCENDING "descending"
#define NAME "name"
#define	STAR_RATING "star_rating"
#define STANDARD_ROOM_PRICE "standard_room_price"
#define DELUXE_ROOM_PRICE "deluxe_room_price"
#define LUXURY_ROOM_PRICE "luxury_room_price"
#define PREMIUM_ROOM_PRICE "premium_room_price"
#define AVERAGE_ROOM_PRICE "average_room_price"
#define FOUR 4
#define TWELVE 12
#define DEFAULT_PRICE_FILTER "default_price_filter"
#define ACTIVE "active"
#define TRUE "true"
#define FALSE "false"
#define RATING_OVERALL "rating_overall"
#define MANUAL_WEIGHTS "manual_weights"
#define RATING_PERSONAL "rating_personal"
#define EPSILON 0.0001
#define THOUSAND 1000
#define ESTIMATED_WEIGHTS "estimated_weights"
#define CITY "city"
#define MIN_STAR "min_star"
#define MAX_STAR "max_star"
#define MIN_PRICE "min_price"
#define MAX_PRICE "max_price"
#define TYPE "type"
#define QUANTITY "quantity"
#define CHECK_IN "check_in"
#define CHECK_OUT "check_out"
#define STANDARD "standard"
#define DELUXE "deluxe"
#define LUXURY "luxury"
#define PREMIUM "premium"
#define ID_ "id: "
#define HOTEL_ "hotel: "
#define ROOM_ "room: "
#define QUANTITY_ "quantity: "
#define COST_ "cost: "
#define CHECK_IN_ "check_in "
#define CHECK_OUT_ "check_out "
#define SPACE ' '
#define THIRTY 30
#define EMPTY "Empty"
#define STAR "star"
#define CITY "city"
#define PRICE "price"
#define ROOM "room"
#define TEN 10
#define DEFAULT_PRINT_SENT "* Results have been filtered by the default price filter."
#define LOCATION_ "location: "
#define	CLEANLINESS_ "cleanliness: "
#define STAFF_ "staff: "
#define FACILITIES_ "facilities: "
#define VALUE_FOR_MONEY_ "value_for_money: "
#define OVERALL_RATING_ "overall_rating: "
#define FOUR 4
#define STAR_ "star: "
#define OVERVIEW_ "overview: "
#define AMENITIES_ "amenities: "
#define CITY_ "city: "
#define LONGITUDE_ "longitude: "
#define LATITUDE_ "latitude: "
#define ROOMS__ "#rooms: "
#define PRICE_ "price: "
#define standard_name "s"
#define deluxury_name "d"
#define luxury_name "l"
#define premium_name "p"
#define SPACE ' '