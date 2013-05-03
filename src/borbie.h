#ifndef BORBIE_H
#define BORBIE_H

#include <irrlicht.h>
#include "gameObject.h"
#include "audioSystem.h"
#include "random.h"

class GameInstance;

class Borbie : public GameObject{

  public:
   Borbie(GameInstance *gameInstance); 
   int getScore();
   void updateScore(int addition);
   void ricochet();
   void applyBulletDamage(int amount);

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

    SoundClip *ricochet1;
	SoundClip *ricochet2;
	SoundClip *ricochet3;
    SoundClip *bulletHit1;
    SoundClip *bulletHit2;
    SoundClip *bulletHit3;
    SoundClip *bulletHit4;
    SoundClip *bulletHit5;
    SoundClip *bulletHit6;
    SoundClip *bulletHit7;
};

#endif
