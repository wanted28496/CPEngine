#include"PlayerInstance.h"
#include"Player.h"

Player* PlayerInstance::p;

void PlayerInstance::SetInstance(Player **i_p) {
	PlayerInstance::p = *i_p;
}

Player* PlayerInstance::GetInstance() {
	return PlayerInstance::p;
}