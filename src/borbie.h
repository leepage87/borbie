#ifndef BORBIE_H
#define BORBIE_H

#include <irrlicht.h>
#include "gameObject.h"

class GameInstance;

class Borbie : public GameObject{

  public:
   Borbie(GameInstance *gameInstance); 
   
   int getScore();
   void updateScore(int addition);
   
   virtual void applyCollision(
			irr::scene::IMetaTriangleSelector *metaTriSelector);	

  //getters
   irr::scene::ICameraSceneNode* getCamera()
   {
     return this->camera;
   }


  private:
   int score;
   irr::scene::ICameraSceneNode* camera;
};

#endif
