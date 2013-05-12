/*********************************************************************
 * File:     soldier.cpp
 * Authors:  Richard Teammco, Lee Page, Jonathan Miodownik
 * Function: This abstract class creates regular sized soldiers so you
 *           can throw cars at them and shit. Also allows them to aim
 *           their weapon and fire.
 *********************************************************************/

#include "soldier.h"
#include "gameInstance.h"
#include "mapSearcher.h"

#include <vector>


using namespace irr;
using namespace scene;
using namespace core;
using namespace video;

/*********************************************************************
 * Constructor for the big ass soldier
 * Param: gameInstance the game instance containing all necessary pointers
 * Param: posX the X coordinate at which the soldier will be spawned
 * Param: posY the Y coordinate at which the soldier will be spawned
 * Param: posZ the Z coordinate at which the soldier will be spawned
 *********************************************************************/
Soldier::Soldier(
	GameInstance *gameInstance,
	float posX, float posY, float posZ)
	// call super GameObject constructor first:
	: GameObject(gameInstance)
{
    this->BULLET_DAMAGE = 3;
    this->objectType = TYPE_ENEMY;
    this->sceneNode = smgr->addMeshSceneNode(
    	smgr->getMesh("assets/models/enemies/soldier/armydude.obj"));
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

/*********************************************************************
 * Applies collision to the model created
 * Param: metaTriSelector pointer to the IMetaFriangleSelector
 *        that handles collision
 *********************************************************************/
void Soldier::applyCollision(
	irr::scene::IMetaTriangleSelector *metaTriSelector){
	// add its triangles to the global collision meta selector
	ITriangleSelector *selector =
		smgr->createTriangleSelectorFromBoundingBox(sceneNode);
	sceneNode->setTriangleSelector(selector);
	selector->drop();
	metaTriSelector->addTriangleSelector(sceneNode->getTriangleSelector());
}

/*********************************************************************
 * An updater method that calls aim() if the soldier has LOS
 * on the player, also calls setMoving
 *********************************************************************/
void Soldier::update(){
    int distance = lookAtPlayer();
    aim(distance);
    checkMovement(distance);
    checkProximity(distance);
    setMoving();
}

/*********************************************************************
 * Orients the soldier towards the player's position (i.e. the solider
 * turns to look at the player). Also, sets the length variable, which
 * indicates the distance between this soldier and the player.
 * Returns: int resembling the distance (in game units) to the player.
 *********************************************************************/
int Soldier::lookAtPlayer(){
	vector3df start = sceneNode->getPosition();
	start.Y += 75;
	vector3df end = gameInstance->getCamera()->getPosition();
	end.Y -= 150;
	vector3df vect = end-start;
	sceneNode->setRotation(vect.getHorizontalAngle());
	return (f32)start.getDistanceFrom(end);
}

/*********************************************************************
 * Checks if player is within line of sight and within range of firing.
 * If so, attempts to shoot at the player.
 *********************************************************************/
void Soldier::aim(int distance){
    //Tactically attempt to bust a cap if Borbie is
    //within 6000 units
	if (distance < 6000 && canShoot())
        fire(distance);
}

/*********************************************************************
 * Checks distance to player, and if the player is too far away, makes
 * an effort to either walk to the player in a straight line (if
 * possible) or else use the A-Star algorithm to find a path to the
 * player using the roads.
 *********************************************************************/
void Soldier::checkMovement(int distance){
    //Tactically operate oneself towards the enemy (Borbie)
    //if enemy distance is between 10k-2k and borbie is visible
    if (!moving && distance < 10000 && distance > 2000 && isPlayerVisible())
        moveToPlayer();
    //If length is high enough and can't see Borbie, use the A* pathfinding
    //algorithm to move over to Borbie if not already moving somewhere
    else if(!moving && distance > 6000 && !isPlayerVisible())
        aStarToPlayer();
}

/*********************************************************************
 * Checks proximity to the
 *********************************************************************/
void Soldier::checkProximity(int distance){
    //stomp him in the nuts
    if (distance < 200){
        this->gameInstance->player->deathStomp();
        explode();
    }
}

/*********************************************************************
 * Sets the moving field to false once the soldier gets to
 * his destination
 *********************************************************************/
void Soldier::setMoving(){
    if (sceneNode->getPosition() == destination)
        moving = false;
}

/*********************************************************************
 * Casts a ray to determine whether or not the soldier can see
 * the player for use with movement and shooting
 * Returns: a boolean value
 *********************************************************************/
bool Soldier::isPlayerVisible(){
    ray.end = sceneNode->getPosition();
	ray.start = gameInstance->getCamera()->getPosition();

	ISceneCollisionManager* collMan =
	    gameInstance->getSceneManager()->getSceneCollisionManager();
	vector3df intersection;
	triangle3df hitTriangle;

	ISceneNode * selected =
		collMan->getSceneNodeAndCollisionPointFromRay(
		ray, intersection, hitTriangle, IDFlag_IsPickable, 0);
    if (selected == sceneNode)//Direct line of sight
        return true;
    return false;	
}

/*********************************************************************
 * Moves the soldier toward the enemy, only gets called when
 * there is a direct line of sight
 *********************************************************************/
void Soldier::moveToPlayer(){
    moving = true;
    vector3df start = sceneNode->getPosition();
    destination = gameInstance->getCamera()->getPosition();
    destination.X = start.X + 0.2*(destination.X-start.X);
    destination.Z = start.Z + 0.2*(destination.Z-start.Z);
    destination.Y = 70;//ground height
    f32 length = (f32)ray.start.getDistanceFrom(destination);
    const int SOLDIER_MOVE_SPEED = 1.5;
    f32 time = length * SOLDIER_MOVE_SPEED;
    ISceneNodeAnimator* anim =
            gameInstance->getSceneManager()->createFlyStraightAnimator(start,
            destination, time, false);
    sceneNode->addAnimator(anim);
    anim->drop();
}

/*********************************************************************
 * Moves the soldier toward the Borbie over a longer distance, using
 * A* algorithm to find a shortest path using roads.
 *********************************************************************/
void Soldier::aStarToPlayer(){
    // Find shortest path using the MapSearcher from this soldier to the player
    //  using the closest available road intersection points.
    MapSearcher *searcher = this->gameInstance->getMapSearcher();
    vector3df curPosition = this->sceneNode->getPosition();
    std::vector<RoadIntersection> path = searcher->getShortestPath(
	    curPosition,
	    this->gameInstance->getCamera()->getPosition());
    
    // If path is unavailable, or already near Borbie, do nothing.
    int numPathPoints = path.size();
    if(numPathPoints == 0)
        return;
    
    // set up a list of coordinates to move through, starting with the
    //  soldier's current position.
    array<vector3df> coords;
    coords.push_back(this->sceneNode->getPosition());
    for(int i=0; i<numPathPoints; ++i){
        vector3df point;
        point.X = path[i].X;
        point.Y = curPosition.Y;
        point.Z = path[i].Y;
        coords.push_back(point);
    }
    
    // set the destination to the location of the last coordinate
    this->destination.X = path[numPathPoints-1].X;
    this->destination.Y = curPosition.Y;
    this->destination.Z = path[numPathPoints-1].Y;
    
    // create a spline animator (follows the path of coordinates) to animate
    //  the soldier to move to Borbie.
    ISceneNodeAnimator *anim = smgr->createFollowSplineAnimator(
        this->gameInstance->currentGameTime, coords, 0.1f, 0.0, false);
    sceneNode->addAnimator(anim);
    anim->drop();
    moving = true;
}

/*********************************************************************
 * Tests to see if the soldier is allowed to shoot, returns
 * true if the fireDelay time has passed, false if otherwise
 * Returns: a boolean value
 *********************************************************************/
bool Soldier::canShoot(){
	unsigned int currentTime = gameInstance->currentGameTime;
	if (currentTime - lastFireTime  > fireDelay && isPlayerVisible()){
		return true;
    }
	return false;
}

/*********************************************************************
 * Animates a muzzle flash billboard with firing sound and does
 * damage to borbie.  This method is only called when the soldier
 * is within range and has direct line of sight.  He has an 80%
 * chance of hitting his target.
 *********************************************************************/
void Soldier::fire(int distance){
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
	
	ISceneNodeAnimator* anim =
	    gameInstance->getSceneManager()->createDeleteAnimator(MUZZLE_FLASH_TIME);
	bill->addAnimator(anim);
	anim->drop();
    if (!miss(distance))
	    gameInstance->player->applyBulletDamage(BULLET_DAMAGE);
    else
        gameInstance->player->ricochet();		
}

/*********************************************************************
 * Gets a random number between 0 and 5, if the number is less
 * than .
 * Returns: a boolean value, true being a miss.
 *********************************************************************/
bool Soldier::miss(int distance){
    // lower distance = lower offset value (approx 1 offset per 1000 distance)
    int offset = distance / 600;
    // at  6k distance, offset = 10, 11-offset = 1,  1/10  chance to hit
    // at  3k distance, offset = 5,  11-offset = 6,  6/10  chance to hit
    // at <1k distance, offset = 1,  11-offset = 10, 10/10 chance to hit
    if (Random::randomInt(10) < 11-offset){//chance to NOT miss
        return false;
    }
    return true;
}

/*********************************************************************
 * Gets an integer between 1 and 4 to use as the time between
 * each shot
 * Returns: random integer between 1000 and 4000
 *********************************************************************/
int Soldier::getRandomFireDelay(){
    return Random::randomInt(1, 5)*1000;
}

/*********************************************************************
 * Causes this soldier to explode, making it vanish, and return a particle
 * effect node animating the explosion effect in its current position.
 *********************************************************************/
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
}
