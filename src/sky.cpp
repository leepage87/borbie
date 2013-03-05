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
scene::ISceneNode* skybox=smgr->addSkyBoxSceneNode(
		driver->getTexture("assets/textures/calm_top.jpg"),
		driver->getTexture("assets/textures/calm_top.jpg"),
		driver->getTexture("assets/textures/calm_left.jpg"),
		driver->getTexture("assets/textures/calm_right.jpg"),
		driver->getTexture("assets/textures/calm_front.jpg"),
		driver->getTexture("assets/textures/calm_back.jpg"));
	scene::ISceneNode* skydome=smgr->addSkyDomeSceneNode(driver->getTexture("assets/textures/skydome.jpg"),16,8,0.95f,2.0f);

  skybox->setVisible(true);
}
