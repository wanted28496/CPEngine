#include"Monster.h"
#include"Point2D.h"
#include"CharacterName.h"
#include"PlayerInstance.h"
#include"Player.h"
#include<stdlib.h>

Monster::Monster() {
}

Monster::Monster(char* i_value) {
	name = new CharacterName(i_value);
	location = new Point2D(rand() % 100, rand() % 100);
	Duration(rand() % 10 + 5);
	next = nullptr;
	isHead = false;
}

Monster::~Monster() {
	if (name)
		delete name;
	if (location)
		delete location;
	if (next)
		delete next;
}

Monster& Monster::operator=(Monster i_rhs) {
	this->location = i_rhs.Location();
	this->name->Name(i_rhs.Name());
	this->isHead = i_rhs.IsHead();
	this->next = i_rhs.Next();
	this->duration = i_rhs.Duration();
	return  *this;
}
Monster& Monster::operator=(Monster *i_rhs) {
	this->location = i_rhs->Location();
	this->name->Name(i_rhs->Name());
	this->isHead = i_rhs->IsHead();
	this->next = i_rhs->Next();
	this->duration = i_rhs->Duration();
	return  *this;
}


//Reutrn the next monster address
Monster* Monster::Next() const { return next; }

//Return if the Monster isHead or not
bool Monster::IsHead() const { return isHead; }

//Return the location of Monster
Point2D* Monster::Location() const { return location; }

//retrun the monsterName of monster
char* Monster::Name() const { return name->Name(); }

//retrun the duration of monster
int Monster::Duration() const { return duration; }

// setters

// Sets the next monster in line
void Monster::Next(Monster* i_n) { next = i_n; }

//set the head of array of the Monster 
void Monster::IsHead(bool i_head) { isHead = i_head; }


//set the duration of monster
void Monster::Duration(int i_value) { duration = i_value; }

// set the name of monster
void Monster::Name(char* i_value) { name->Name(i_value); }

void Monster::Name(CharacterName* i_name) { name = i_name; }

/**
set the values of location using Point2D
@param i_point object of Point2D class
*/
void Monster::Location(Point2D *i_point) {
	location = i_point;
}

/**
set the values of location using Point2D
@param i_x integer value for x axis
@param i_y integer value for y axis
*/
void Monster::Location(const int i_x, const int i_y) {
	location->X(i_x);
	location->Y(i_y);
}

/**
Calculates where the monster should go

@param object monster object whoes direction is to be found
@param player player object to check for location of player
@retrun character value for the direction of monster
*/

void Monster::GetMonsterDirection(Point2D **loc) {
	Player* player = PlayerInstance::GetInstance();
	Point2D* direction = *loc;
	
	int x_diff = direction->X() - player->Location()->X();
	int y_diff = direction->Y() - player->Location()->Y();
	int diff = x_diff - y_diff;
	if (x_diff >= 0) {
		if (y_diff >= 0) {
			if (diff >= 0) {
				direction->X(direction->X() - 1);
				direction->Y(direction->Y() + 0);
			}
			else {
				direction->X(direction->X() + 0);
				direction->Y(direction->Y() - 1);
			}
		}
		else {
			diff = x_diff + y_diff;
			if (diff >= 0) {
				direction->X(direction->X() + 0);
				direction->Y(direction->Y() + 1);
			}
			else {
				direction->X(direction->X() - 1);
				direction->Y(direction->Y() + 0);
			}
		}
	}
	else {
		if (y_diff >= 0) {
			diff = x_diff + y_diff;
			if (diff >= 0) {
				direction->X(direction->X() + 0);
				direction->Y(direction->Y() - 1);
			}
			else {
				direction->X(direction->X() + 1);
				direction->Y(direction->Y() + 0);
			}
		}
		else {
			if (diff >= 0) {
				direction->X(direction->X() + 0);
				direction->Y(direction->Y() + 1);
			}
			else {
				direction->X(direction->X() + 1);
				direction->Y(direction->Y() + 0);
			}
		}
	}

}

void Monster::UpdateLocation() {
	GetMonsterDirection(&location);
}