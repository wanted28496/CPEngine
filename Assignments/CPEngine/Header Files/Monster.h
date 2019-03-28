#pragma once
/**
Monster.h
purpose: Controller Class for Monsters
@author Mit Doshi
@version 1.1 12/16/2018
*/

#include"IObjectController.h"

class Point2D;
class CharacterName;

class Monster : public IObjectController {
public:

	Monster();
	Monster(char* i_value);
	~Monster();
	Monster& operator=(Monster i_monster);
	Monster& operator=(Monster *i_monster);

	void UpdateLocation() override;
	Monster* Next() const;
	bool IsHead() const;
	Point2D* Location() const;
	char* Name() const;
	int Duration() const;

	void Next(Monster* i_n);
	void IsHead(bool i_head);
	void Duration(int i_value);
	void Name(char* i_value);
	void Name(CharacterName* i_name);
	void Location(Point2D *i_point);
	void Location(const int i_x, const int i_y);

private:
	CharacterName * name;
	Point2D* location;
	int duration;
	Monster* next;
	bool isHead;

	void GetMonsterDirection(Point2D **loc);

};