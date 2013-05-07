/*	File: soldier.cpp
 *	Authors:  tkys
 *	
 *	This class creates soldiers so you can throw cars at them and shit
 */

#include "soldier.h"
#include "gameInstance.h"

using namespace std;

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;

/*************************************************************
 * Constructor for the big ass soldier
 * Param: gameInstance the game instance containing all necessary pointers
 * Param: posX the X coordinate at which the soldier will be spawned
 * Param: posY the Y coordinate at which the soldier will be spawned
 * Param: posZ the Z coordinate at which the soldier will be spawned
 *************************************************************/
Soldier::Soldier(
	GameInstance *gameInstance,
	float posX, float posY, float posZ)
	// call super GameObject constructor first:
	: GameObject(gameInstance)
{
    this->BULLET_DAMAGE = 3;
    this->objectType = TYPE_ENEMY;
    this->sceneNode =
    	smgr->addMeshSceneNode(smgr->getMesh("assets/models/enemies/soldier/armydude.obj"));
	this->sceneNode->setPosition(vector3df(posX, posY, posZ));
	this->sceneNode->setScale(vector3df(10,10,10));
	this->sceneNode->setVisible(true);
	this->sceneNode->setMaterialFlag(EMF_LIGHTING, true);
	this->sceneNode->setID(IDFlag_IsPickable);
	this->setHealth(400);
	this->lastFireTime = 0;
	this->moving = false;
    this->fireDelay = getRandomFireDelay();
    this->explosionDamage = 1;
    this->explosionRadius = 50;
}

/*************************************************************
 * Applies collision to the model created
 * Param: metaTriSelector pointer to the IMetaFriangleSelector
 *        that handles collision
 ************************************************************/
void Soldier::applyCollision(
	irr::scene::IMetaTriangleSelector *metaTriSelector){
	// add its triangles to the global collision meta selector
	ITriangleSelector *selector =
		smgr->createTriangleSelectorFromBoundingBox(sceneNode);
	sceneNode->setTriangleSelector(selector);
	selector->drop();
	metaTriSelector->addTriangleSelector(sceneNode->getTriangleSelector());
}
/*************************************************************
 * Gets an integer between 1 and 3 to use as the time between
 * each shot
 * Returns: random integer between 1 and 4
 ************************************************************/
int Soldier::getRandomFireDelay(){
    return Random::randomInt(1, 5)*1000;
}
/*************************************************************
 * An updater method that calls aim() if the soldier has LOS
 * on the player, also calls setMoving
 ************************************************************/
void Soldier::updatePosition(){
    aim();
    setMoving();
}

/*************************************************************
 * Sets the moving field to false once the soldier gets to
 * his destination
 ************************************************************/
void Soldier::setMoving(){
    if (sceneNode->getPosition() == destination)
        moving = false;
}

/*************************************************************
 * Orientates the soldier towards the players position and
 * checks if the player is within moving/shooting distance
 * also explodes the soldier if the player is on top of it
 ************************************************************/
void Soldier::aim(){
	//turn the soldier to look at you
	vector3df start = sceneNode->getPosition();
	start.Y += 75;
	vector3df end = gameInstance->getCamera()->getPosition();
	end.Y -= 150;
	vector3df vect = end-start;
	sceneNode->setRotation(vect.getHorizontalAngle());
	length = (f32)start.getDistanceFrom(end);
    
	//Tactically operate oneself towards the enemy (Borbie)
    //if enemy distance is between 10k-2k and borbie is visible
    if (!moving && length < 10000 && length > 2000 && visible())
        move();
    //Tactically attempt to bust a cap if Borbie is
    //within 6000 units
	if (length < 6000 && canShoot())
            fire();	
    //stomp him in the nuts
    if (length < 200){
        this->audioSystem->playSound3d(gameInstance->death1,this);
        explode();
    }
}

/*************************************************************
 * Casts a ray to determine whether or not the soldier can see
 * the player for use with movement and shooting
 * Returns: a boolean value
 ************************************************************/
bool Soldier::visible(){
    ray.end = sceneNode->getPosition();
	ray.start = gameInstance->getCamera()->getPosition();

	ISceneCollisionManager* collMan = gameInstance->getSceneManager()->getSceneCollisionManager();
	vector3df intersection;
	triangle3df hitTriangle;

	ISceneNode * selected =
		collMan->getSceneNodeAndCollisionPointFromRay(
		ray, intersection, hitTriangle, IDFlag_IsPickable, 0);
    if (selected == sceneNode)//Direct line of sight
        return true;
    return false;	
}

/*************************************************************
 * Moves the soldier toward the enemy, only gets called when
 * there is a direct line of sight
 ************************************************************/
void Soldier::move(){
    moving = true;
    vector3df start = sceneNode->getPosition();
    destination = gameInstance->getCamera()->getPosition();
    destination.X = start.X + 0.2*(destination.X-start.X);
    destination.Z = start.Z + 0.2*(destination.Z-start.Z);
    destination.Y = 70;//ground height
    length = (f32)ray.start.getDistanceFrom(destination);
    const int SOLDIER_MOVE_SPEED = 1.5;
    f32 time = length * SOLDIER_MOVE_SPEED;
    ISceneNodeAnimator* anim =
            gameInstance->getSceneManager()->createFlyStraightAnimator(start,
            destination, time, false);
    sceneNode->addAnimator(anim);
    anim->drop();
}

/*************************************************************
 * Tests to see if the soldier is allowed to shoot, returns
 * true if the fireDelay time has passed, false if otherwise
 * Returns: a boolean value
 ************************************************************/
bool Soldier::canShoot(){
	unsigned int currentTime = gameInstance->getDevice()->getTimer()->getTime();
	if (currentTime - lastFireTime  > fireDelay && visible()){
		return true;
    }
	return false;
}

/*************************************************************
 * Animates a muzzle flash billboard with firing sound and does
 * damage to borbie.  This method is only called when the soldier
 * is within range and has direct line of sight.  He has an 80%
 * chance of hitting his target.
 ************************************************************/
void Soldier::fire(){
	lastFireTime = gameInstance->getDevice()->getTimer()->getTime();
	IBillboardSceneNode * bill;
	bill = smgr->addBillboardSceneNode();
	bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
    bill->setMaterialTexture(0, driver->getTexture("assets/textures/muzFlash.png"));
	bill->setMaterialFlag(video::EMF_LIGHTING, false);
	bill->setMaterialFlag(video::EMF_ZBUFFER, false);
	float randomNum = Random::randomFloat(-10.0, 15.0);
	bill->setSize(core::dimension2d<f32>(30.0+randomNum, 30.0+randomNum));
	bill->setID(0);//not pickable by ray caster
		
	//get enemy position, adjust muzzle flash height to barrel
	vector3df start = sceneNode->getPosition();
	start.Y+=60;
	bill->setPosition(start);

    this->audioSystem->playSound3d(gameInstance->gunShot1,
	    this);
	
	const int MUZZLE_FLASH_TIME = 50;
	
	ISceneNodeAnimator* anim = gameInstance->getSceneManager()->createDeleteAnimator(MUZZLE_FLASH_TIME);
	bill->addAnimator(anim);
	anim->drop();
    if (!miss())
	    gameInstance->player->applyBulletDamage(BULLET_DAMAGE);
    else
        gameInstance->player->ricochet();		
}

/*************************************************************
 * Gets a random number between 1 and 5, if the number is less
 * than or equal to 5 the soldier has hit his target (80%).
 * Returns: a boolean value
 ************************************************************/
bool Soldier::miss(){
    if (Random::randomInt(1,6) <= 5){//20% chance
        return false;
    }
    return true;
}

// Causes this object to explode, making it vanish, and return a particle
//	effect node animating the explosion effect in its current position.
void Soldier::createExplosionEffect(){
	// add a new explosion particle systems (for the two intermixed explosions)
    this->explosionParticleSystem =
		this->smgr->addParticleSystemSceneNode(false);
    this->explosionParticleSystemLarge =
        this->smgr->addParticleSystemSceneNode(false);
    
	// add an emitter for BLOODSPLOSION!!!!!!!!!!!!!!!
	IParticleEmitter *explosionEmitter =
	    this->explosionParticleSystem->createBoxEmitter(
		    aabbox3d<f32>(-5, 0, -5, 5, 1, 5),  // emitter size
		    vector3df(0.0f,0.0f,0.1f),          // direction + speed
		    2000, 5000,                       // min,max particles per second
		    SColor(0,255,255,255),              // darkest color
		    SColor(0,255,255,255),              // brightest color
		    200, 800,                          // min, max particle lifetime
		    360,                                // max angle degrees
		    dimension2df(40.0f, 40.0f),         // min start size
		    dimension2df(200.0f, 200.0f));        // max start size
	this->explosionParticleSystem->setEmitter(explosionEmitter);
	explosionEmitter->drop(); // drop (re-created later)
	
	//add gravity affector to BLOODSPLOSION!!!!!!!!!!!!
	IParticleGravityAffector* pgaf = explosionParticleSystem->createGravityAffector
											(vector3df(0.F,-0.2F,0.0F), 200U);
	explosionParticleSystem->addAffector(pgaf);
    pgaf->drop();

	// add fade-out affector to the BLOODSPLOSION!!!!!!!!!!!!
	IParticleAffector* explosionFadeOutAffector =
	    explosionParticleSystem->createFadeOutParticleAffector();
	this->explosionParticleSystem->addAffector(explosionFadeOutAffector);
	explosionFadeOutAffector->drop();
	
	// customize the particle system positioning, etc.
	vector3df explosionPos = this->sceneNode->getPosition();
	if(explosionPos.Y < 0) // adjust position: no explosions underground!
	    explosionPos.Y = 0;

	// adjust the blood
	this->explosionParticleSystem->setPosition(explosionPos);
	this->explosionParticleSystem->setScale(vector3df(45, 45, 45));
	this->explosionParticleSystem->setMaterialFlag(EMF_LIGHTING, false);
	this->explosionParticleSystem->setMaterialFlag(EMF_ZWRITE_ENABLE, false);
	this->explosionParticleSystem->setMaterialTexture(0,
	this->driver->getTexture("assets/textures/blood.bmp"));
	this->explosionParticleSystem->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
	
	std::cout << "Soldier gone boom " << std::endl;
}
