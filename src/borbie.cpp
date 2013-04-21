#include "borbie.h"
#include "gameInstance.h"

#include <iostream> // TODO: debug

using namespace irr;
using namespace gui;
using namespace video;
using namespace core;

Borbie::Borbie(GameInstance *gameInstance) : GameObject(gameInstance){
  this->setHealth(1000);
  this->camera=gameInstance->getCamera();
  this->sceneNode=camera;
}

void Borbie::applyCollision(irr::scene::IMetaTriangleSelector *metaTriSelector) {}




