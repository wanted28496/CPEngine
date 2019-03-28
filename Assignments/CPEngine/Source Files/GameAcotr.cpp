#include<iostream>

#include"GameActor.h"
#include"CharacterName.h"
#include"Point2D.h"

GameActor::GameActor() {
	char* temp = new char[50];
	std::cout << "Please Enter the Name for character: ";
	std::cin >> temp;
	name = new CharacterName(temp);
	location = new Point2D(50, 50);

	delete temp;
}

GameActor::GameActor(char* i_name) {
	Name(i_name);
	Location(50, 50);
}

GameActor::~GameActor() {
	if (name)
		delete name;
	if (location)
		delete location;
}

GameActor& GameActor::operator=(GameActor i_rhs) {
	this->location = i_rhs.Location();
	this->name->Name(i_rhs.Name());
	return  *this;
}

GameActor& GameActor::operator=(GameActor *i_rhs) {
	this->location = i_rhs->Location();
	this->name->Name(i_rhs->Name());
	return  *this;
}


Point2D *GameActor::Location() const { return location; }
char* GameActor::Name() const { return name->Name(); }

// set the name of monster
void GameActor::Name(char* i_value) { name->Name(i_value); }

void GameActor::Name(CharacterName* i_name) { name = i_name; }

/**
set the values of location using Point2D
@param i_point object of Point2D class
*/
void GameActor::Location(Point2D *i_point) {
	location = i_point;
}

/**
set the values of location using Point2D
@param i_x integer value for x axis
@param i_y integer value for y axis
*/
void GameActor::Location(const int i_x, const int i_y) {
	location->X(i_x);
	location->Y(i_y);
}