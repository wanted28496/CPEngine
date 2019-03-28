#pragma once
/**
Player.h
purpose: Controller Class for Player
@author Mit Doshi
@version 1.1 12/16/2018
*/

#include"IObjectController.h"

class Point2D;
class CharacterName;

class Player: public IObjectController {
	
public:
	Player();
	Player(char *i_name);
	Player& operator=(Player rhs);
	Player& operator=(Player *rhs);
	~Player();


	Point2D* Location() const;
	char* Name() const;
	char Option() const;
	
	void Name(char* i_value);

	void Name(CharacterName* i_name);

	void Location(Point2D *i_point);

	void Location(const int i_x, const int i_y);

	void UpdateLocation() override;

private:
	CharacterName* name;
	Point2D* location;
	char option;

	char GetOptionFromPlayer();
	void GetPlayerMovement(char option, Point2D **loc);

};