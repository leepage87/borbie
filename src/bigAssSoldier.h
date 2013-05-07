#ifndef BIG_ASS_SOLDIER_H
#define BIG_ASS_SOLDIER_H

#include <iostream> // TODO: debug (remove)

#include <irrlicht.h>

#include "gameObject.h"
#include "audioSystem.h"
#include "random.h"
#include "soldier.h"

// define GameInstance to use pointer
class GameInstance;


class BigAssSoldier : public virtual Soldier {

	public:
	BigAssSoldier(
	    GameInstance *gameInstance,
		float posX, float posY, float posZ);
};
#endif
