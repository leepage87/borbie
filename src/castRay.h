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


// pickable stuff
enum PickingIDs {
	IDFlag_IsNotPickable = 0,               // 0
	IDFlag_IsPickable = 1 << 0,             // 1 
	IDFlag_IsHighlightable = 1 << 1         // 2 
};


// CastRay class:
class CastRay {
  private:
	irr::scene::ISceneManager * smgr;
	irr::scene::ICameraSceneNode *camera;

    // returns the first node in front of the camera up to the given
    //  maximum distance. Returns NULL (0) if nothing is in range.
    irr::scene::ISceneNode* getTarget(float distance);

  public:
	CastRay(
        irr::scene::ISceneManager *smgr,
        irr::scene::ICameraSceneNode *camera);
	
    // Returns the node of the nearest object when clicked, up to a
    //  distance of 400 game units.
	irr::scene::ISceneNode* getTarget(); // DEPRECATED: use getClickTarget()
    irr::scene::ISceneNode* getClickTarget();
    irr::scene::ISceneNode* getClickTargetShort();

    // Returns the node of the nearest object thrown at, up to a
    //  distance of ??? game units.
    irr::scene::ISceneNode* getThrowTarget();
	
}; // end of CastRay class


#endif
