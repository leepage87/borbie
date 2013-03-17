/*	File: castRay.h
 *	Authors: teamKillYourself
 *
 *	Description: this file contains the class declaration of the
 *	ray caster, which allows the user to mouseover and select objects
 */

#ifndef CAST_RAY_H
#define CAST_RAY_H


// include irrlicht
#include <irrlicht.h>


// CastRay class:
class CastRay {
	public:
	irr::scene::ISceneManager * smgr;
	irr::scene::ICameraSceneNode *camera;


  //public:
	CastRay(irr::scene::ISceneManager *smgr, irr::scene::ICameraSceneNode *camera );
	
	irr::scene::ISceneNode* getTarget();
	
}; // end of CastRay class


#endif
