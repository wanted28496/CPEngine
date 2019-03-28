#pragma once
/**
Gameobject.h
purpose: Third Controller class
@author Mit Doshi
@version 1.3 3/17/2019
*/

#include"IObjectController.h"
#include"SmartPointer.h"

class Point2D;
class CharacterName;

class GameObjects {
public:
	GameObjects() = delete;
	static SmartPointer<GameObjects> Create(const Point2D&, const char *, const Point2D&);
	GameObjects(const Point2D, const char*, const Point2D);
	~GameObjects();

	//Method for getting object location
	Point2D Location() const;

	Point2D Velocity() const;

	//Method for getting object name
	char* Name() const;


	void Location(const Point2D &i_point);
	void Location(const float i_x, const float i_y);
	
	void Velocity(const Point2D &i_point);
	void Velocity(const float i_x, const float i_y);
	
	void Name(const CharacterName &i_value);
	void Name(char* i_value);
	
private:
	Point2D* m_velocity;
	Point2D* m_location;
	CharacterName* m_name;
};