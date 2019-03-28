/**
 GameObjects.cpp
 purpose: Base Class for all objects in game with name and a 2D location
 @author Mit Doshi
 @version 1.3 3/17/2019
*/
#include"GameObject.h"
#include"Point2D.h"
#include"CharacterName.h"

//TODO::Make Everthing WeakPointers
#pragma region Overload Methods


SmartPointer<GameObjects> GameObjects::Create(const Point2D& i_pos, const char * i_name, const Point2D& i_velocity) {
	return SmartPointer<GameObjects>(new GameObjects(i_pos, i_name, i_velocity));
}

GameObjects::GameObjects(const Point2D i_pos,const char* i_name,const Point2D i_velocity) {
	m_location = new Point2D(i_pos);
	m_velocity = new Point2D(i_velocity);
	m_name = new CharacterName(i_name);
}

GameObjects::~GameObjects() {
	/*if (m_location)
		delete m_location;
	if (m_velocity)
		delete m_velocity;*/
}

#pragma endregion

#pragma region Getter Setter

#pragma region Velocity
/**
	set the values of velocity using Point2D
	@param i_point object of Point2D class
*/
void GameObjects::Velocity(const Point2D &i_velocity) {
	*m_velocity = i_velocity;
}

/**
	set the values of Velocity using Point2D
	@param i_x integer value for x axis
	@param i_y integer value for y axis
*/
void GameObjects::Velocity(const float i_x, const float i_y) {
	m_velocity->X(i_x);
	m_velocity->Y(i_y);
}

Point2D GameObjects::Velocity() const {
	return *m_velocity;
}

#pragma endregion

#pragma region Location
/**
	set the values of location using Point2D
	@param i_point object of Point2D class
*/
void GameObjects::Location(const Point2D &i_point) {
	*m_location = i_point;
}


/**
	set the values of location using Point2D
	@param i_x integer value for x axis
	@param i_y integer value for y axis
*/
void GameObjects::Location(const float i_x, const float i_y) {
	m_location->X(i_x);
	m_location->Y(i_y);
}

Point2D GameObjects::Location() const {
	return *m_location;
}

#pragma endregion

#pragma region Name

/**
	set the name of object using CharacterName Class object
	@param i_value object of CharacterName class
*/
void GameObjects::Name(const CharacterName &i_value) {
	*m_name = i_value;
}

/**
	set the name of object using char pointer
	@param i_value pointer to a char
*/
void GameObjects::Name(char* i_value) {
	m_name->Name(i_value);
}

char* GameObjects::Name() const {
	return m_name->Name();
}

#pragma endregion

#pragma endregion



