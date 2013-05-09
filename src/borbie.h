/*********************************************************************
 * File:     borbie.h
 * Authors:  Richard Teammco, Lee Page, Jonathan Miodownik
 * Function: This is the header file for borbie.cpp
 *********************************************************************/

#ifndef BORBIE_H
#define BORBIE_H

#include <irrlicht.h>
#include "gameObject.h"
#include "audioSystem.h"
#include "random.h"


enum PlayerMode {
    PLAYER_MODE_OK_HEALTH,
    PLAYER_MODE_LOW_HEALTH,
    PLAYER_MODE_DEAD
};

class GameInstance;

class Borbie : public GameObject{

   public:
   Borbie(GameInstance *gameInstance); 
   ~Borbie();
   int getScore();
   void updateScore(int addition);
   void ricochet();
   void applyBulletDamage(int amount);
   void deathStomp();
   virtual void applyCollision(
			irr::scene::IMetaTriangleSelector *metaTriSelector);	

  //getters
   irr::scene::ICameraSceneNode* getCamera(){ return this->camera; }
   
   PlayerMode playerMode;
   PlayerMode getMode();
   void setMode(PlayerMode mode);




  private:
    int score;
    bool hasPlayed;
    
    irr::scene::ICameraSceneNode* camera;

    //Bullet miss sounds
    SoundClip *ricochet1;
	SoundClip *ricochet2;
	SoundClip *ricochet3;

    //Bullet hit sounds
    SoundClip *bulletHit1;
    SoundClip *bulletHit2;
    SoundClip *bulletHit3;
    SoundClip *bulletHit4;
    SoundClip *bulletHit5;
    SoundClip *bulletHit6;
    SoundClip *bulletHit7;

    //Soldier deathstomp sounds
    SoundClip *death1;
    SoundClip *death2;
    SoundClip *death3;
    SoundClip *death4;

    //Low health sounds
    SoundClip *lowHealth1;
    SoundClip *lowHealth2;

    void playBulletHit();
};

#endif
