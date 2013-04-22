#ifndef SOLDIER_H
#define SOLDIER_H


#include <irrlicht.h>
#include "game_object.h"


// define GameInstance to use pointer
class GameInstance;


class Soldier : public GameObject {
	//private:
	//irr::scene::IAnimatedMeshSceneNode *sceneNode;
	
	public:
	Soldier(
	    GameInstance *gameInstance,
		float posX, float posY, float posZ);

	virtual void applyCollision(
			irr::scene::IMetaTriangleSelector *metaTriSelector
		);
	void fire();
};
#endif
