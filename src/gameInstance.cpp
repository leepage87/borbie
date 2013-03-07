#include "gameInstance.h"
#include "Terrain.h"
#include "sky.h"

using namespace irr;
using namespace scene;
using namespace video;
using namespace core;

GameInstance::GameInstance(ISceneManager *smgr, IVideoDriver *driver ){
	// keep pointers to Irrlicht rendering pointers
	this->smgr = smgr;
	this->driver = driver;
	
	// setup global collision meta selector
	this->metaTriSelector = smgr->createMetaTriangleSelector();
		
	//create a temp camera for testing
	//TODO remove temp camera

	ICameraSceneNode *camera = smgr->addCameraSceneNodeFPS(0, 100.0f, 1.2f);
	camera->setPosition(vector3df(2700*2,255*2,2600*2));
	camera->setFarValue(30000.0f); 
	Terrain *terr = new Terrain(driver, smgr, camera);  

	Sky *s = new Sky(smgr, driver);
  

}


// Add a node's Traingle Selector to the global meta selector. Use
//	irr::scene::ISceneNode->getTriangleSelector() to get one.
//	Make sure to set it up first with:
//	smgr->createTriangleSelectorFromBoundingBox(node); (or something)
void GameInstance::addCollision(irr::scene::ITriangleSelector *selector){
	this->metaTriSelector->addTriangleSelector(selector);
}

// Remove a node's Triangle Selector from the global meta selector.
void GameInstance::removeCollision(irr::scene::ITriangleSelector *selector){
	this->metaTriSelector->removeTriangleSelector(curModel->getTriangleSelector());
}























// empty space just cuz it's cool
