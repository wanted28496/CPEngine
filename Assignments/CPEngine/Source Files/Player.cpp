#include"Player.h"
#include"Point2D.h"
#include"CharacterName.h"
#include<iostream>

Player::Player() {
	char* temp = new char[50];
	std::cout << "Please Enter the Name for character: ";
	std::cin >> temp;
	name = new CharacterName(temp);
	location = new Point2D(50, 50);
	
	delete temp;
}

Player::Player(char* i_name) {
	Name(i_name);
	Location(50, 50);
}

Player::~Player() {
	if (name)
		delete name;
	if (location)
		delete location;
}

Player& Player::operator=(Player i_rhs) {
	this->location = i_rhs.Location();
	this->name->Name(i_rhs.Name());
	return  *this;
}

Player& Player::operator=(Player *i_rhs) {
	this->location = i_rhs->Location();
	this->name->Name(i_rhs->Name());
	return  *this;
}


Point2D *Player::Location() const { return location; }
char* Player::Name() const { return name->Name(); }

// set the name of monster
void Player::Name(char* i_value) { name->Name(i_value); }

void Player::Name(CharacterName* i_name) { name = i_name; }

/**
set the values of location using Point2D
@param i_point object of Point2D class
*/
void Player::Location(Point2D *i_point) {
	location = i_point;
}

/**
set the values of location using Point2D
@param i_x integer value for x axis
@param i_y integer value for y axis
*/
void Player::Location(const int i_x, const int i_y) {
	location->X(i_x);
	location->Y(i_y);
}


void Player::UpdateLocation() {
	option = GetOptionFromPlayer();
	GetPlayerMovement(option, &location);
}

char Player::Option() const {
	return option;
}

char Player::GetOptionFromPlayer() {
	char c;
	std::cin >> c;
	return c;
}


/**
Calculates where the player should go after decideing

@param option character option selected by user
@return a Point2D location for movement
*/
void Player::GetPlayerMovement(char option, Point2D **loc) {
	Point2D* direction = *loc;
	switch (option) {
	case 'w':
		direction->X(direction->X() + 0);
		direction->Y(direction->Y() + 1);
		break;
	case 'a':
		direction->X(direction->X() - 1);
		direction->Y(direction->Y() + 0);
		break;
	case 's':
		direction->X(direction->X() + 0);
		direction->Y(direction->Y() - 1);
		break;
	case 'd':
		direction->X(direction->X() + 1);
		direction->Y(direction->Y() + 0);
		break;
	default:
		direction->X(direction->X() + 0);
		direction->Y(direction->Y() + 0);
	}
}