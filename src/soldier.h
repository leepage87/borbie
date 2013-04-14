#ifndef SOLDIER_H
#define SOLDIER_H


#include <irrlicht.h>
#include "enemy.h"

class Soldier : public Enemy {
	public:
	Soldier(irr::scene::ISceneManager *smgr,
	    irr::video::IVideoDriver *driver,
	    irr::IrrlichtDevice *device,
		float posX, float posY, float posZ);
};

#endif
