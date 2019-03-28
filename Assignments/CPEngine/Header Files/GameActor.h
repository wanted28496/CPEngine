#pragma once

class Point2D;
class CharacterName;

class GameActor {

	GameActor();
	GameActor(char *i_name);
	GameActor& operator=(GameActor rhs);
	GameActor& operator=(GameActor *rhs);
	~GameActor();


	Point2D* Location() const;
	char* Name() const;
	char Option() const;

	void Name(char* i_value);

	void Name(CharacterName* i_name);

	void Location(Point2D *i_point);

	void Location(const int i_x, const int i_y);

private:
	Point2D * location;
	CharacterName * name;
};