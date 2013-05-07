#include "borbie.h"
#include "gameInstance.h"

#include <iostream> // TODO: debug

using namespace irr;
using namespace gui;
using namespace video;
using namespace core;

Borbie::Borbie(GameInstance *gameInstance) : GameObject(gameInstance){
  this->objectType = TYPE_BORBIE;
  
  this->score=0;
  this->setHealth(1000);
  this->camera=gameInstance->getCamera();
  this->sceneNode=camera;
  this->ricochet1 = audioSystem->createSound3d("assets/sounds/soundEffects/bullets/ricochet.mp3");
  this->ricochet2 = audioSystem->createSound3d("assets/sounds/soundEffects/bullets/ricochet2.mp3");
  this->ricochet3 = audioSystem->createSound3d("assets/sounds/soundEffects/bullets/ricochet3.mp3");
  this->bulletHit1 = audioSystem->createSound3d("assets/sounds/soundEffects/bullets/bulletHit.mp3");
  this->bulletHit2 = audioSystem->createSound3d("assets/sounds/soundEffects/bullets/bulletHit2.mp3");
  this->bulletHit3 = audioSystem->createSound3d("assets/sounds/soundEffects/bullets/bulletHit3.mp3");
  this->bulletHit4 = audioSystem->createSound3d("assets/sounds/soundEffects/bullets/bulletHit4.mp3");
  this->bulletHit5 = audioSystem->createSound3d("assets/sounds/soundEffects/bullets/bulletHit5.mp3");
  this->bulletHit6 = audioSystem->createSound3d("assets/sounds/soundEffects/bullets/bulletHit6.mp3");
  this->bulletHit7 = audioSystem->createSound3d("assets/sounds/soundEffects/bullets/bulletHit7.mp3");
}

void Borbie::applyCollision(irr::scene::IMetaTriangleSelector *metaTriSelector) {}


int Borbie::getScore()
{
  return score;
}

void Borbie::updateScore(int addition)
{
 score+=addition; 
}
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
void Borbie::applyBulletDamage(int amount){
    this->health -= amount;
    playBulletHit();
    if(this->health <= 0){
        this->health = 0;
        std::cout << "BORBIE DEAD LOL" << std::endl;
        this->explode();
    }
}

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
