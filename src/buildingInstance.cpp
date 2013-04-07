/*	File: buildingInstance.cpp
 *	Authors: idk your names
 *
 *	Description: this file contains the class declaration of the
 *	building instance object. The building object provides a specification
 *	of the abstract GameObject class and contains functions and variables
 *	specific to destructable buildings placed within the environment.
 */

#include "buildingInstance.h"

#include <iostream> // TODO: debug (remove)
using namespace std;

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;


BuildingInstance::BuildingInstance(
	ISceneManager *smgr,
	IVideoDriver *driver,
	float width, float height, float depth,
	float posX, float posY, float posZ,
	ITexture *texture)
	: GameObject(smgr, driver) // call super GameObject constructor first
{
    // calculate y-position based on height (with posY being the base
    //  of the building. Irrlicht centers objects at 1/2 height.
    float actualPosY = posY + (height * 10) / 2;
    
    // set x,z positions based on width and depth respectively (center it)
    float actualPosX = posX + (width * 10) / 2;
    float actualPosZ = posZ + (depth * 10) / 2;
    
	this->sceneNode = smgr->addCubeSceneNode();
	this->sceneNode->setScale(vector3df(width, height, depth));
	this->sceneNode->setPosition(vector3df(actualPosX, actualPosY , actualPosZ));
	this->sceneNode->setMaterialTexture(0, texture);
	this->sceneNode->setMaterialFlag(EMF_LIGHTING, true);
	this->sceneNode->addShadowVolumeSceneNode(0,-1,true,25.0f);
	
	this->fireParticleSystem = 0;
	this->sparkParticleSystem = 0;
	this->height = height;
	this->posY = posY;
}


BuildingInstance::~BuildingInstance(){
	if(this->fireParticleSystem)
		this->fireParticleSystem->remove();
}


void BuildingInstance::doDamage(int damage){
	this->health -= damage;
}


// Adds a triangle selector to the given meta triangle selectior to add this
//  building's collision detection to the global collision meta. The collision
//  selector is given from the scene node's bounding box, which matches the
//  visible object exactly since it is just a cube.
void BuildingInstance::applyCollision(
	irr::scene::IMetaTriangleSelector *metaTriSelector)
{
	// add its triangles to the global collision meta selector
	ITriangleSelector *selector =
		smgr->createTriangleSelectorFromBoundingBox(sceneNode);
	sceneNode->setTriangleSelector(selector);
	selector->drop();
	metaTriSelector->addTriangleSelector(sceneNode->getTriangleSelector());
}


// Sets this building on fire. Oh boy.
// (adds a fire animation to the building model using particle effects)
void BuildingInstance::setAblaze(){
    // ADD FIRE EFFECT
    // if a particle system for fire already exists, clean it off
    if(this->fireParticleSystem)
        this->fireParticleSystem->remove();
    
    this->fireParticleSystem =
		this->smgr->addParticleSystemSceneNode(false);
	
	// determine min and max lifetime based on height (25===1500)
	float maxLifetime = 45 * this->height;
	float minLifetime = maxLifetime/5;
	
	// add the fire emitter to the fire particle system
	IParticleEmitter *fireEmitter = this->fireParticleSystem->createBoxEmitter(
		aabbox3d<f32>(-5, 0, -5, 5, 1, 5),  // emitter size
		vector3df(0.0f,0.3f,0.0f),          // direction + speed
		3000, 8000,                         // min,max particles per second
		SColor(0,255,255,255),              // darkest color
		SColor(0,255,255,255),              // brightest color
		minLifetime, maxLifetime,           // min, max particle lifetime
		0,                                  // max angle degrees
		dimension2df(30.f,30.f),            // min start size
		dimension2df(50.f,50.f));           // max start size
	this->fireParticleSystem->setEmitter(fireEmitter); // this grabs the emitter
	fireEmitter->drop(); // so we can drop it here without deleting it
	
	// add fade-out affector to the fire particle system
	IParticleAffector* fireFadeOutAffector =
	    this->fireParticleSystem->createFadeOutParticleAffector();
	this->fireParticleSystem->addAffector(fireFadeOutAffector);
	fireFadeOutAffector->drop();
	
	// customize the fire particle system positioning, etc.
	vector3df pos = this->sceneNode->getPosition();
	pos.Y = this->posY - this->height/2; // get actual y-position
	this->fireParticleSystem->setPosition(pos);
	this->fireParticleSystem->setScale(vector3df(45, 45, 45));
	this->fireParticleSystem->setMaterialFlag(EMF_LIGHTING, false);
	this->fireParticleSystem->setMaterialFlag(EMF_ZWRITE_ENABLE, false);
	this->fireParticleSystem->setMaterialTexture(0,
	    this->driver->getTexture("assets/textures/fire.bmp")); // fire colored
	this->fireParticleSystem->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
	
	
    // ADD SPARKS EFFECT
    // if a particle system for fire already exists, clean it off
    if(this->sparkParticleSystem)
        this->sparkParticleSystem->remove();
    
    this->sparkParticleSystem =
		this->smgr->addParticleSystemSceneNode(false);
	
	// add the spark emitter to the spark particle system
	IParticleEmitter *sparkEmitter = this->sparkParticleSystem->createBoxEmitter(
		aabbox3d<f32>(-5, 0, -5, 5, this->height/8, 5),  // emitter size
		vector3df(0.0f, 0.8f, 0.0f),        // direction + speed
		250, 1200,                          // min,max particles per second
		SColor(0,255,255,255),              // darkest color
		SColor(0,255,255,255),              // brightest color
		800, 850,                           // min, max particle lifetime
		360,                                // max angle degrees (spread out)
		dimension2df(30.f,30.f),            // min start size
		dimension2df(40.f,40.f));           // max start size
	this->sparkParticleSystem->setEmitter(sparkEmitter);
	sparkEmitter->drop();
	
	// add a fade-out affector to the spark particle system
	IParticleAffector* sparkFadeOutAffector =
	    this->sparkParticleSystem->createFadeOutParticleAffector();
	this->sparkParticleSystem->addAffector(sparkFadeOutAffector);
	sparkFadeOutAffector->drop();
	
	// customize the particle system positioning, etc.
	this->sparkParticleSystem->setPosition(pos); // add to same pos as fire
	this->sparkParticleSystem->setScale(vector3df(45, 45, 45));
	this->sparkParticleSystem->setMaterialFlag(EMF_LIGHTING, false);
	this->sparkParticleSystem->setMaterialFlag(EMF_ZWRITE_ENABLE, false);
	this->sparkParticleSystem->setMaterialTexture(0,
	    this->driver->getTexture("assets/textures/pinkfire.bmp")); // pink
	this->sparkParticleSystem->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
}
