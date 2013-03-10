/*
* Lee Page
* Sky object (sky.h)
* CIS 395 
*/
#include "sky.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


#define s2( name ) #name
#define stringify( name ) s2( name )

Sky::Sky(ISceneManager * smgr, IVideoDriver *driver) {
	scene::ISceneNode* skydome=smgr->addSkyDomeSceneNode(driver->getTexture("assets/textures/burnies.jpg"),16,8,0.95f,2.0f);

  skydome->setVisible(true);
}
