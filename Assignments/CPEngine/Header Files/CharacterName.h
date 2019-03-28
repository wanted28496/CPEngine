#pragma once
/**
CharacterName.h
purpose: stores the name of character
@author Mit Doshi
@version 1.1 12/16/2018
*/

class CharacterName {
public:
	CharacterName();
	CharacterName(const char* i_value);

	CharacterName& operator=(const CharacterName i_rhs);
	CharacterName& operator=(const CharacterName *i_rhs);
	//getter methods for private variables

	char* Name() const;
	int Length() const;
	
	void Name(const char* i_value);

	~CharacterName();

private:
	char* name;
	int length;

	const int SetLength(const char* i_value);
};

