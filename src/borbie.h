#ifndef BORBIE_H
#define BORBIE_H

#include <irrlicht.h>
#include "game_object.h"

class GameInstance;

class Borbie : public GameObject{

  public:
   Borbie(GameInstance *gameInstance); 
   
   
   virtual void applyCollision(
			irr::scene::IMetaTriangleSelector *metaTriSelector);	

};

#endif
