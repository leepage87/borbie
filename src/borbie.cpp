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

