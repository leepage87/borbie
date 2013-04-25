/*	File: buildingInstance.cpp
 *	Authors: idk your names
 *
 *	Description: this file contains the class declaration of the
 *	building instance object. The building object provides a specification
 *	of the abstract GameObject class and contains functions and variables
 *	specific to destructable buildings placed within the environment.
 */

#include "vehicleInstance.h"
#include "random.h"

#include <iostream> // TODO: debug (remove)
using namespace std;

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;


VehicleInstance::VehicleInstance(
	GameInstance *gameInstance,
	float posX, float posY, float posZ, IAnimatedMesh *mesh, int model)
	// call super GameObject constructor first:
	: GameObject(gameInstance)
{
	this->model = model;
    this->motionAnimator = 0;
    this->lastIntersection = 0;
    this->nextIntersection = 0;
    
	this->sceneNode = smgr->addMeshSceneNode(mesh);
	if (model == 0){//its a jeep
		this->sceneNode->setScale(vector3df(.2, .2, .2));
	}else{//its a riviera
		this->sceneNode->setScale(vector3df(40,40,40));
	}
	this->sceneNode->setPosition(vector3df(posX, posY+20 , posZ));
	this->sceneNode->setMaterialFlag(EMF_LIGHTING, true);
	//this->sceneNode->addShadowVolumeSceneNode(0,-1,true,25.0f);
}

VehicleInstance::~VehicleInstance(){
    if(this->motionAnimator)
        this->motionAnimator->drop();
}

// Set the next intersection of this vehicle (where to go).
void VehicleInstance::setNextIntersection(RoadIntersection *nextIntersection) {
    this->nextIntersection = nextIntersection;
}
	
// Start moving towards the next intersection.
void VehicleInstance::go() {
    // make sure nextIntersection is set!
    if(!this->nextIntersection)
        return;
    
    // Start animating to next point:
    vector3df startPoint = this->sceneNode->getPosition();
    vector3df endPoint;
    endPoint.X = this->nextIntersection->X;
    endPoint.Y = startPoint.Y;
    endPoint.Z = this->nextIntersection->Y;
	f32 length = (f32)(endPoint - startPoint).getLength();
	const f32 SPEED = 0.9f;
	u32 time = (u32)(length / SPEED);
    this->motionAnimator = this->smgr->createFlyStraightAnimator(
            startPoint,
            endPoint,
		    time
       );
    this->sceneNode->addAnimator(this->motionAnimator);
	if(model == 0)//its a jeep
		sceneNode->setRotation((endPoint-startPoint).getHorizontalAngle());
	else//its a buick
		sceneNode->setRotation((startPoint-endPoint).getHorizontalAngle());
}

// Stops moving and removes all animators.
void VehicleInstance::stop() {
    if(this->motionAnimator){
        this->sceneNode->removeAnimators();
        this->motionAnimator->drop();
        this->motionAnimator = 0;
    }
}

	
// Updates animator checks. If animation done, selects next random
//  position to go to.
void VehicleInstance::updateMovement() {
    // If animation is done, remove animator and switch to next node.
    if(this->motionAnimator && this->motionAnimator->hasFinished()){
        this->motionAnimator->drop();
        
        // randomly choose a new intersection. If none are available,
        //  choose to go back.
        int numAvailablePaths = this->nextIntersection->connections.size();
        
        // If no paths available, do nothing.
        if(numAvailablePaths == 0)
            return;
        
        // If only one path is available, animate to that path, even if
        //  if means going back again.
        else if(numAvailablePaths == 1){ // if only one path, go to it
            this->lastIntersection = this->nextIntersection;
            this->nextIntersection = this->nextIntersection->connections[0];
        }
        
        // If more than one path is available, randomly choose a path that
        //  is not the same as where the vehicle just came from.
        else {
            // TODO - this is bias. Path in list after the one we just came
            //  from gets a random weight of 2.
            int pathIndex = Random::randomInt(numAvailablePaths);
            if( this->nextIntersection->connections[pathIndex] ==
                this->lastIntersection)
            {
                pathIndex++;
                if(pathIndex >= numAvailablePaths)
                    pathIndex = 0; // wrap index around if necessary
            }
            this->lastIntersection = this->nextIntersection;
            this->nextIntersection =
                this->nextIntersection->connections[pathIndex];
        }
        
        std::cout << "Switching paths." << std::endl;
        this->go();
    }
}


void VehicleInstance::applyCollision(
	irr::scene::IMetaTriangleSelector *metaTriSelector)
{
	// add its triangles to the global collision meta selector
	ITriangleSelector *selector =
		smgr->createTriangleSelectorFromBoundingBox(sceneNode);
	sceneNode->setTriangleSelector(selector);
	selector->drop();
	metaTriSelector->addTriangleSelector(sceneNode->getTriangleSelector());
	
	// get bounds
	/*core::aabbox3d<f32> modelBounds = this->sceneNode->getTransformedBoundingBox();
	// add a collision response animator to it
	core::vector3df radius = modelBounds.MaxEdge - modelBounds.getCenter();
	ISceneNodeAnimator* anim = this->smgr->createCollisionResponseAnimator(
		metaTriSelector, this->sceneNode,
		radius, // radius of collision
		vector3df(0, -5, 0), // gravity (negative y = down)
		vector3df(0, -radius.Y, 0)); // radius offset
	this->sceneNode->addAnimator(anim);
	anim->drop();*/
}
