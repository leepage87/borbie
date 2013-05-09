/*********************************************************************
 * File:     borbie.cpp
 * Authors:  Richard Teammco, Lee Page, Jonathan Miodownik
 * Function: This class extends gameObject and holds all the information
 *           relating to borbie's health as well as the sounds played
 *           when she is damaged.
 *********************************************************************/
#include "borbie.h"
#include "gameInstance.h"


using namespace irr;
using namespace gui;
using namespace video;
using namespace core;

/*********************************************************************
 * Constructor for the borbie object, this object holds the player's
 * health and bullet hit/miss sound effects, extends gameObject
 * Param: gameInstance the game instance containing all necessary pointers
 *********************************************************************/
Borbie::Borbie(GameInstance *gameInstance) : GameObject(gameInstance){
  this->objectType = TYPE_BORBIE;
  this->score=0;
  this->setHealth(1000);
  this->camera=gameInstance->getCamera();
  this->sceneNode=camera;
  this->ricochet1 = audioSystem->
    createSound3d("assets/sounds/soundEffects/bullets/ricochet.mp3");
  this->ricochet2 = audioSystem->
    createSound3d("assets/sounds/soundEffects/bullets/ricochet2.mp3");
  this->ricochet3 = audioSystem->
    createSound3d("assets/sounds/soundEffects/bullets/ricochet3.mp3");
  this->bulletHit1 = audioSystem->
    createSound3d("assets/sounds/soundEffects/bullets/bulletHit.mp3");
  this->bulletHit2 = audioSystem->
    createSound3d("assets/sounds/soundEffects/bullets/bulletHit2.mp3");
  this->bulletHit3 = audioSystem->
    createSound3d("assets/sounds/soundEffects/bullets/bulletHit3.mp3");
  this->bulletHit4 = audioSystem->
    createSound3d("assets/sounds/soundEffects/bullets/bulletHit4.mp3");
  this->bulletHit5 = audioSystem->
    createSound3d("assets/sounds/soundEffects/bullets/bulletHit5.mp3");
  this->bulletHit6 = audioSystem->
    createSound3d("assets/sounds/soundEffects/bullets/bulletHit6.mp3");
  this->bulletHit7 = audioSystem->
    createSound3d("assets/sounds/soundEffects/bullets/bulletHit7.mp3");
  this->death1 = audioSystem->
    createSound3d("assets/sounds/soundEffects/meinLeiben.wav");
  this->death2 = audioSystem->
    createSound3d("assets/sounds/soundEffects/armyDeath.wav");
  this->death3 = audioSystem->
    createSound3d("assets/sounds/soundEffects/armyDeath2.wav");
  this->death4 = audioSystem->
    createSound3d("assets/sounds/soundEffects/gib.mp3");
}

/*************************************************************************
Desctructor, checks if each sound exists.  If the sound is loaded, delete it.
*************************************************************************/
Borbie::~Borbie(){
    if (bulletHit1)
        bulletHit1->release();
    if (bulletHit2)
        bulletHit2->release();
    if (bulletHit3)
        bulletHit3->release();
    if (bulletHit4)
        bulletHit4->release();
    if (bulletHit5)
        bulletHit5->release();
    if (bulletHit6)
        bulletHit6->release();
    if (bulletHit7)
        bulletHit7->release();
    if (ricochet1)
        ricochet1->release();
    if (ricochet2)
        ricochet2->release();
    if (ricochet3)
        ricochet3->release();
    if (death1)
        death1->release();
    if (death2)
        death2->release();
    if (death3)
        death3->release();
    if (death4)
        death4->release();
}

/*********************************************************************
 * Overrides the gameObject's applyCollision method in favor of the
 * FPS camera's collision
 *********************************************************************/
void Borbie::applyCollision(irr::scene::IMetaTriangleSelector *metaTriSelector) {}

/*********************************************************************
 * Returns the player's score for use with the HUD
 * Return: score an integer representing the player's score
 *********************************************************************/
int Borbie::getScore()
{
  return score;
}

/*********************************************************************
 * Updates the integer value containing the player's score
 *********************************************************************/
void Borbie::updateScore(int addition)
{
 score+=addition; 
}

/*********************************************************************
 * Plays a ricochet sound in the case of a bullet miss
 *********************************************************************/
void Borbie::ricochet(){
    int num = Random::randomInt(0, 4);
    switch (num){
        case 0:
            this->audioSystem->playSound3d(ricochet1, this);         
            break;
        case 1:
            this->audioSystem->playSound3d(ricochet2, this); 
            break;
        case 3:
            this->audioSystem->playSound3d(ricochet3, this); 
            break;
    }
}

/*********************************************************************
 * Decrements the player's health by the given amount, also checks if
 * the player's health is less than or equal to zero, and kills the player.
 * Param: amount the amount of damage to do to the player
 *********************************************************************/
void Borbie::applyBulletDamage(int amount){
    this->health -= amount;
    playBulletHit();
    if(this->health <= 0){
        this->health = 0;
        this->explode();
    }
}

/*********************************************************************
 * Plays the sound of a bullet hitting flesh
 *********************************************************************/
void Borbie::playBulletHit(){
    int num = Random::randomInt(0, 7);
    switch (num){
        case 0:
            this->audioSystem->playSound3d(bulletHit1, this);         
            break;
        case 1:
            this->audioSystem->playSound3d(bulletHit2, this); 
            break;
        case 2:
            this->audioSystem->playSound3d(bulletHit3, this); 
            break;
        case 3:
            this->audioSystem->playSound3d(bulletHit4, this); 
            break;
        case 4:
            this->audioSystem->playSound3d(bulletHit5, this); 
            break;
        case 5:
            this->audioSystem->playSound3d(bulletHit6, this); 
            break;
        case 6:
            this->audioSystem->playSound3d(bulletHit7, this); 
            break;
    }
}

/*************************************************************************
Plays death sounds (taken from DOOM) when soldiers get stepped on.
When the soldiers themselves were playing the sound, it was cutting out.
*************************************************************************/
void Borbie::deathStomp(){
    int num = Random::randomInt(4);
    switch (num){
        case 0:
            this->audioSystem->playSound3d(death1, this);
        case 1:
            this->audioSystem->playSound3d(death2, this);
        case 2:
            this->audioSystem->playSound3d(death3, this);
        case 3:
            this->audioSystem->playSound3d(death4, this);
    }
}
