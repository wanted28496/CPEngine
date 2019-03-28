#pragma once
/**
PlayerInstance.h
purpose: Stores static instance of player
@author Mit Doshi
@version 1.1 12/16/2018
*/

class Player;

class PlayerInstance {
public:
	static void SetInstance(Player **i_p);
	static Player* GetInstance();
	static Player* p;
};