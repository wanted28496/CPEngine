#include "CharacterName.h"
#include<iostream>
CharacterName::CharacterName()
{


}
CharacterName::CharacterName(const char* i_value) {
	Name(i_value);
}

CharacterName& CharacterName::operator=(const CharacterName i_rhs) {
	this->Name(i_rhs.Name());
	return *this;
}

CharacterName& CharacterName::operator=(const CharacterName *i_rhs) {
	this->Name(i_rhs->Name());
	return *this;
}

//getter methods for private variables
char* CharacterName::Name() const { return name; }
int CharacterName::Length() const { return length; }

void CharacterName::Name(const char* i_value) {
	if (name)
		delete name;
	const int len = SetLength(i_value);
	name = new char[len];
	for (int i = 0; i < length - 1; i++) {
		name[i] = i_value[i];
	}
	name[length - 1] = '\0';
}

CharacterName::~CharacterName() {
	if (name)
		delete name;
}
const int CharacterName::SetLength(const char* i_value) {
	length = 1;
	for (int i = 0; i_value[i] != '\0'; i++) {
		length++;
	}
	const int a = length;
	return a;
}