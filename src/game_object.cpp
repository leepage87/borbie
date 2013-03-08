#include "game_object.h"


GameObject::GameObject(){
	this->health = GAME_OBJ_MAXHEALTH;
}

int GameObject::getHealth() const {
	return this->health;
}
