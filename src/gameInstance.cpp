#include "gameInstance.h"
#include "Terrain.h"
#include "sky.h"

using namespace irr;
using namespace scene;
using namespace video;
using namespace core;

GameInstance::GameInstance(ISceneManager *smgr, IVideoDriver *driver ){
	this->smgr = smgr;
  this->driver = driver; 
    
  //create a temp camera for testing
  //TODO remove temp camera

  ICameraSceneNode *camera = smgr->addCameraSceneNodeFPS(0, 100.0f, 1.2f);
  camera->setPosition(vector3df(2700*2,255*2,2600*2));
  camera->setFarValue(30000.0f); 
  Terrain *terr = new Terrain(driver, smgr, camera);  

  Sky *s = new Sky(smgr, driver);
  

}
