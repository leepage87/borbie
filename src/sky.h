/*
* Lee Page et al
* Sky object (sky.h)
* CIS 395 
*/
#ifndef SKY_H
#define SKY_H

#include <string>
#include <irrlicht.h>

class Sky {
private:

	irr::scene::ISceneManager * smgr;
public:
	irr::scene::ISceneNode * sky;

	Sky(irr::scene::ISceneManager * smgr, irr::video::IVideoDriver *driver);

	irr::scene::ISceneNode* getNode() { return sky; }
};
#endif
