#ifndef SOLDIER_H
#define SOLDIER_H


#include <irrlicht.h>
#include "game_object.h"

class Soldier : public GameObject {
	private:
	irr::scene::IAnimatedMeshSceneNode *sceneNode;
	irr::scene::IBillboardSceneNode * bill;
	
	public:
	Soldier(irr::scene::ISceneManager *smgr,
	    irr::video::IVideoDriver *driver,
	    irr::IrrlichtDevice *device,
		float posX, float posY, float posZ);

	virtual void doDamage(int damage);

	virtual void applyCollision(
			irr::scene::IMetaTriangleSelector *metaTriSelector
		);

	//void fire();
};
#endif
