#include "gameInstance.h"
#include "game.h"
#include "keyBindings.h"
#include "mapReader.h"
#include "borbie.h"

#include <iostream> // TODO - remove (debug)

#include "mapSearcher.h" // TODO - remove
#include "random.h" // TODO - remove
#include <vector> // TODO remove

using namespace irr;
using namespace scene;
using namespace video;
using namespace core;
using namespace gui;


// GAMEPLAY CONSTANTS
const float BORBIE_PUNCH_DAMAGE = 75;
const float BORBIE_PUNCH_DELAY_MS = 250;


// CONSTRUCTOR:
//  builds the GameInstance object and initializes all internal game objects,
//  such as buildings, vehicles, etc.
GameInstance::GameInstance(
    ISceneManager *smgr,
    IGUIEnvironment *guienv,
    IVideoDriver *driver,
    IrrlichtDevice *device,
    AudioSystem *audioSystem,
    unsigned int runMode,
    IEventReceiver *receiver,
    Game *game)
{

  this->game=game;


  /*** Setup Pointers and Irrlicht Objects ***/    

  // keep pointers to Irrlicht rendering pointers
  this->smgr = smgr;
  this->guienv = guienv;
  this->driver = driver;
  this->device = device;
  this->audioSystem = audioSystem;
  this->receiver = receiver;
  this->timer = device->getTimer();

  // initialize all game timers to 0
  this->currentGameTime = 0;
  this->nextPunchTime = 0;

  ((BorbiesEventReceiver*)(this->receiver))->setGameInstance(this);


  /*** Setup Sounds and Music ***/

  this->bgSound = audioSystem->createSound2d("assets/sounds/yumyum.ogg");
  this->bgSoundDead = audioSystem->createSound2d("assets/sounds/angryWorld.ogg");
  //Start the shitty music and loop! 
  audioSystem->playMusicLoop(bgSound); 
  audioSystem->setMusicVolume(0.15);
  // setup global collision meta selector
  this->metaTriSelector = smgr->createMetaTriangleSelector();

  this->burningSound =
    audioSystem->createSound3d("assets/sounds/soundEffects/burning.mp3");
  this->explosionSound1 =
    audioSystem->createSound3d("assets/sounds/soundEffects/rocketHit.wav");
  this->death1 =
    audioSystem->createSound3d("assets/sounds/soundEffects/meinLeiben.wav");
  this->gunShot1 =
    audioSystem->createSound3d("assets/sounds/soundEffects/burst.mp3");  
  this->gunShot2 =
    audioSystem->createSound3d("assets/sounds/soundEffects/bigAssGun.mp3");  
  /*** Setup Runtime Flags ***/

  float gravity = GLOBAL_GRAVITY;
  bool noVerticalMovement = true; // disabled
  float playerMoveSpeed = PLAYER_MOVEMENT_SPEED;

  // if debug mode, turn off gravity and enable vertical movement
  if(runMode & BORBIE_DEBUG_MODE){
    gravity = 0.f; // no gravity
    noVerticalMovement = false; // vertical movement enabled
    playerMoveSpeed = PLAYER_MOVEMENT_SPEED_DEBUG;
  }


  /*** create textures for in game menu ***/
  this->menu = driver->getTexture("assets/textures/deathMenu.jpg");



  /*** Setup Environment ***/

  // Add Terrain and collision
  this->terrain = new Terrain(driver, smgr, metaTriSelector);
  addCollision(this->terrain->getTriSelector());

  // add skybox
  this->skybox = new Sky(smgr, driver);

  // add lighting
  this->light = new WorldLight(smgr);

  //set shadow color: dark purplish
  smgr->setShadowColor(video::SColor(120,35,20,47));

  this->rainParticleSystem = 0;


  /*** Setup Game Objects (BUILDINGS, VEHICLES) ***/

  // Read the map file into the global static MapReader object.
  this->mapReader = new MapReader("assets/map/coords.bor");
  this->mapSearcher = this->mapReader->getMapSearcher();

  // add the buildings and generate city based on coordinate file
  this->buildings = new Buildings(metaTriSelector, this);
  this->buildings->generateObjects();

  // add the vehicles and generate initial spawns
  this->vehicles = new Vehicles(metaTriSelector, this);
  this->vehicles->generateObjects();

  // default vehicle throwing variables to nothing
  this->carriedVehicle = 0;
  this->vehicleThrown = false;
  this->targetPos = vector3df(0,0,0);
  
  // add and generate enemies
  this->enemies = new Enemies (metaTriSelector, this);
  this->enemies->generateObjects();



  /*** Setup User Interface (HUD) ***/

  // add the hud object
  this->hud = new Hud(this);



  /*** Setup Camera ***/

  // set key bindings (WASD=move, SPACE=jump) to camera
  SKeyMap keyMap[9];
  KeyBindings *keys = new KeyBindings(&keyMap[0]);
  keys->setKeys();
  // added: (remove if setKeys() becomes static)
  delete keys;

  // setup camera
  camera = smgr->addCameraSceneNodeFPS(
      0,						// parent (none)
      PLAYER_ROTATE_SPEED,	// rotate speed
      playerMoveSpeed,        // move speed
      IDFlag_IsPickable,		// ID
      keyMap,					// keymap
      9,						// keymap size
      noVerticalMovement,		// no vertical movement (true = up/down disabled)
      PLAYER_JUMP_SPEED		// jump speed
      );

  // TODO: read camera position from map file
  camera->setPosition(vector3df(2500, 1000, 4450));
  // set view distance
  camera->setFarValue(30000.0f);
  // hide cursor
  device->getCursorControl()->setVisible(false);

  // add automatic collision response to camera
  ISceneNodeAnimator* anim =
    smgr->createCollisionResponseAnimator(metaTriSelector, camera,
        core::vector3df(60, 150, 60), // radius
        core::vector3df(0, gravity, 0), // gravity (negative y = go down)
        core::vector3df(0, PLAYER_HEIGHT, 0), //radius offset
        0.1f); // sliding value TODO tweak as needed
  camera->addAnimator(anim);
  anim->drop();

  //create beatDown ray selector
  selector = new CastRay(smgr, camera);
  highlightedSceneNode = 0;

  //create objectCarrier for picking shit up
  objCarry = new ObjectCarrier(smgr, device, camera);
  //tell the mouse listener that right mouse isn't pressed to start with
  ((BorbiesEventReceiver *)receiver)->setRightMouse(false);

  /*** Add Hands ***/
  
  hands = new Hands(this);  
  
  /*** Add The Borbie ***/

  this->player = new Borbie(this); 	
  
  this->nextScoreEvent = 10000;


  /*** Test Crap ***/

  // TODO- remove
  //this->setWorldState_wrecked();
  this->setWorldState_fabulous();
}


// TODO --- remove this function
void GameInstance::TEST_PATH_FUNCTION_TODO_REMOVE(){
    std::cout << "TEST PATH BUTTON PRESSED" << std::endl;
    
    IMesh *mesh =  smgr->getMesh("assets/models/ah6.3DS");
    ISceneNode *sceneNode = smgr->addMeshSceneNode(mesh);
	sceneNode->setPosition(vector3df(10200, 500, 10200));
	sceneNode->setScale(vector3df(10, 10, 10));
	sceneNode->setMaterialFlag(EMF_LIGHTING, true);
    
    // create a random node at a random place
    /*float X = Random::randomFloat(18000) + 2000;
    float Y = Random::randomFloat(18000) + 2000;
    
    ISceneNode *sceneNode = smgr->addCubeSceneNode();
    sceneNode->setPosition(vector3df(X, 0, Y));
	sceneNode->setScale(vector3df(40, 100, 40));
	
    MapSearcher *searcher = this->mapReader->getMapSearcher();
	std::vector<RoadIntersection> points = searcher->getShortestPath(
	    sceneNode->getPosition(),
	    this->camera->getPosition());
    
    // list of points
    array<vector3df> coords;
    for(int i=0; i<points.size(); ++i){
        vector3df point;
        point.X = points[i].X;
        point.Y = 0;
        point.Z = points[i].Y;
        coords.push_back(point);
    }
    ISceneNodeAnimator *anim = smgr->createFollowSplineAnimator(
        currentGameTime, coords, 1.0f, 0.0);
    sceneNode->addAnimator(anim);
        
	delete searcher;*/
}


// destructor: removes all objects from memory and ensures that the scene
//  manager is completely wiped clean of all Irrlicht objects.
GameInstance::~GameInstance(){
  ((BorbiesEventReceiver*)receiver)->removeGameInstance();
  this->updateList.clear();
  //delete sounds if they exist
  if(bgSound)
    bgSound->release();  
  if(bgSoundDead)
    bgSoundDead->release();
  if(death1)
    death1->release();
  if(explosionSound1)
    explosionSound1->release();
  if(death1)
    death1->release();
  if(gunShot1)
    gunShot1->release();
  if(gunShot2)
    gunShot2->release();

  delete this->terrain;
  delete this->skybox;
  delete this->light;
  delete this->buildings;
  delete this->vehicles;
  delete this->player;
  delete this->selector;
  delete this->objCarry;
  delete this->mapReader;
  delete this->mapSearcher;
  delete this->hands;
  if(this->rainParticleSystem)
    this->rainParticleSystem->remove();
  this->smgr->clear();

  // release all sound clips from memory
  if(this->burningSound)
    this->burningSound->release();

  //turn the mouse cursor back on
  device->getCursorControl()->setVisible(true);
}



/*** GAMEPLAY EVENTS ***/

// Attempt to punch something directly in front of Borbie. Punching can only
//  happen once every two seconds.
void GameInstance::punch() {

  ISceneNode *target = selector->getClickTargetShort();
  // if ready to punch, and not carrying a vehicle, and a target is found
  if(this->currentGameTime >= this->nextPunchTime &&
      !this->carriedVehicle && target)
  {
    // try to get a target, either a building, a vehicle, or an enemy
    GameObject *targetObj = buildings->getObject(target);
    if(!targetObj)
      targetObj = vehicles->getObject(target);
    if(!targetObj)
      targetObj = enemies->getObject(target);

    // if a target object WAS found, proceed to apply damage to it
    if(targetObj){
      hands->punch();
      targetObj->applyDamage(BORBIE_PUNCH_DAMAGE);
      std::cout << "Punched the target" << std::endl;
      this->nextPunchTime = this->currentGameTime + BORBIE_PUNCH_DELAY_MS;
    }
  }
}


void GameInstance::updatePlayerScore(int amount){
    this->player->updateScore(amount);
    if(this->player->getScore() >= this->nextScoreEvent){
        this->nextScoreEvent += 10000;
        this->enemies->addMaxEnemies(10);
    }
        
}


// Apply explosion damage to all objects within the radius of the given
//  gameObject, scaled based on distance from the explosion, up to a maximum
//  damage as dictated by the given object's damage value. Explosions
//  affect vehicles, buildings, enemies, and Borbie.
void GameInstance::applyExplosionDamage(GameObject *explodingObject) {
  // get the exploding object's variables
  ISceneNode *explodingNode = explodingObject->getNode();
  float explosionRadius = explodingObject->getExplosionRadius();
  float explosionDamage = explodingObject->getExplosionDamage();
  vector3df explodePos = explodingNode->getPosition();

  // calculate damage to enemies
  int numEnemies = enemies->objList.size();
  for(int i=0; i<numEnemies; i++){
    //std::cout << "INSIDE FOR ENEMIES, numEnemies: " << numEnemies << std::endl;
    ISceneNode *curNode = enemies->objList[i]->getNode();
    //std::cout<<"getNode has worked"<<std::endl;
    // if current node is the exploding node, ignore it
    if(curNode == explodingNode)
      continue;
    // if current node is NOT visible or if it already blew up, ignore it
    else if(!curNode->isVisible() || enemies->objList[i]->hasExploded())
      continue;
    float distance = curNode->getPosition().getDistanceFrom(explodePos);
    //std::cout<<"got distance"<<std::endl;
    if(distance <= explosionRadius){
      std::cout<<"inside if for explosion radius"<<std::endl;
      int damage = explosionDamage; // max damage
      if(distance > 400){ // if more than 400 away, scale down damage
        float scale = (distance-400) / (explosionRadius-400);
        damage = int(explosionDamage * scale);
      }
      enemies->objList[i]->applyDamage(damage);
      std::cout << "Damaged enemy @distance=" << distance <<
        " for @damage=" << damage << std::endl;
    }
  }

  // calculate damage for buildings
  int numBuild = buildings->objList.size();
  for(int i=0; i<numBuild; i++){
    ISceneNode *curNode = buildings->objList[i]->getNode();
    // if current node is the exploding node, ignore it
    if(curNode == explodingNode)
      continue;
    // if current node is NOT visible, ignore it
    else if(!curNode->isVisible() || buildings->objList[i]->hasExploded())
      continue;
    // otherwise, check if the distance is close enough, and apply damage
    //  based on the distance to the explosion center
    float distance = curNode->getPosition().getDistanceFrom(explodePos);
    if(distance <= explosionRadius){
      int damage = explosionDamage; // max damage
      if(distance > 400){ // if more than 400 away, scale down damage
        float scale = (distance-400) / (explosionRadius-400);
        damage = int(explosionDamage * scale);
      }
      // if the exploding object is a building, reduce splash damage
      //  to prevent instant-killing an entire city. That would suck.
      if(explodingObject->getObjectType() == TYPE_BUILDING)
        damage = damage / 20;
      buildings->objList[i]->applyDamage(damage);
      std::cout << "Damaged building @distance=" << distance <<
        " for @damage=" << damage << std::endl;
    }
  }

  // calculate damage for vehicles
  int numVehicles = vehicles->objList.size();
  for(int i = 0 ; i < numVehicles ; i++){
    ISceneNode *curNode = vehicles->objList[i]->getNode();
    // if current node is the exploding node, ignore it
    if(curNode == explodingNode)
      continue;
    // if current node is NOT visible, ignore it
    else if(!curNode->isVisible() || vehicles->objList[i]->hasExploded())
      continue;
    // otherwise, check if the distance is close enough, and apply damage
    //  based on the distance to the explosion center
    float distance = curNode->getPosition().getDistanceFrom(explodePos);
    if(distance <= explosionRadius){
      int damage = explosionDamage; // max damage
      if(distance > 400){ // if more than 400 away, scale down damage
        float scale = (distance-400) / (explosionRadius-400);
        damage = int(explosionDamage * scale);
      }
      vehicles->objList[i]->applyDamage(damage);
      std::cout << "Damaged vehicle @distance=" << distance <<
        " for @damage=" << damage << std::endl;
    } 
  } 

  // if Borbie is already dead, don't kill her again :(
  if(player->hasExploded())
    return;

  float distance = player->getNode()->getPosition().getDistanceFrom(explodePos);
  if(distance <= explosionRadius){
    int damage = explosionDamage; // max damage
    if(distance > 400){ // if more than 400 away, scale down damage
      float scale = (distance-400) / (explosionRadius-400);
      damage = int(explosionDamage * scale);
    }
    player->applyDamage(damage);
    std::cout << "Damaged borbie @distance=" << distance <<
      " for @damage=" << damage << std::endl;
  }
}



/*** WORLD STATE (ENVIRONMENT/MOOD) SETTERS ***/

// Changes the visible state of the world environment to the given WorldState
//  value
  void GameInstance::setWorldState(WorldState state){
    if(state == GONETOSHIT)
      this->setWorldState_wrecked();
  }

// Set the mood and visible state of the world to a dark and hellish feeling,
//  but of course, preserving Borbie's pink style (because Hell is so much
//  hotter when it's wearing pink).
void GameInstance::setWorldState_wrecked(){
  // add a particle system effect to rain pink debree:
  if(!this->rainParticleSystem)
    this->createRainParticleSystem("assets/textures/darkpinkfire.bmp");

  // add the rain emitter to the rain particle system
  IParticleEmitter *rainEmitter =
    this->rainParticleSystem->createBoxEmitter(
        aabbox3d<f32>(-100, 0, -100, 100, 100, 100),  // emitter size
        vector3df(0.0f, -1.0f, 0.0f),          // direction + speed
        3000, 5000,                       // min,max particles per second
        SColor(0,255,255,255),              // darkest color
        SColor(0,255,255,255),              // brightest color
        500, 1500,                       // min, max particle lifetime
        0,                                // max angle degrees
        dimension2df(20.0f, 20.0f),         // min start size
        dimension2df(60.0f, 60.0f));        // max start size
  this->setRainEmitter(rainEmitter);
  rainEmitter->drop();


  // set the ambiance to dark and ugly
  this->light->setAmbientLight(50, 10, 22);
}


// Set the mood and visible state of the world to a light, happy "fabulous"
//  mode - bright pink sparkles lightly fall from the sky.
void GameInstance::setWorldState_fabulous() {
  // add a particle system effect to rain pink debree:
  if(this->rainParticleSystem)
    this->rainParticleSystem->drop();
  this->createRainParticleSystem("assets/textures/pinkfire.bmp");

  // add the rain emitter to the rain particle system
  IParticleEmitter *rainEmitter =
    this->rainParticleSystem->createBoxEmitter(
        aabbox3d<f32>(-100, 0, -100, 100, 100, 100),  // emitter size
        vector3df(0.0f, -0.5f, 0.0f),          // direction + speed
        100, 200,                       // min,max particles per second
        SColor(0,255,255,255),              // darkest color
        SColor(0,255,255,255),              // brightest color
        500, 3000,                       // min, max particle lifetime
        0,                                // max angle degrees
        dimension2df(20.0f, 20.0f),         // min start size
        dimension2df(60.0f, 60.0f));        // max start size
  this->setRainEmitter(rainEmitter);
  rainEmitter->drop();

  // set the ambiance to pretty
  this->light->setAmbientLight(255, 172, 253);
}


// Sets the rain source to the current emitter, and automatically adds fade-out
//  affector.
// TODO: fix this to pass in values instead of an emitter pointer
void GameInstance::setRainEmitter(IParticleEmitter *rainEmitter){
  this->rainParticleSystem->setEmitter(rainEmitter);

  // add fade-out affector to the fire particle system
  IParticleAffector* rainFadeOutAffector =
    this->rainParticleSystem->createFadeOutParticleAffector();
  this->rainParticleSystem->addAffector(rainFadeOutAffector);
  rainFadeOutAffector->drop();
}


// Creates a rain particle system above the world map, but does not start making
//  particles yet.
void GameInstance::createRainParticleSystem(const char *texture){
  // if not yet created, create the particle system
  this->rainParticleSystem =
    this->smgr->addParticleSystemSceneNode(false);

  // customize the rain particle system positioning, etc.
  // TODO - allow for arbitrary centering over map terrain
  vector3df pos(10200, 1200, 10200); // center map, 1000 units high
  this->rainParticleSystem->setPosition(pos);
  this->rainParticleSystem->setScale(vector3df(104, 104, 104));
  this->rainParticleSystem->setMaterialFlag(EMF_LIGHTING, false);
  this->rainParticleSystem->setMaterialFlag(EMF_ZWRITE_ENABLE, false);
  this->rainParticleSystem->setMaterialTexture(0,
      this->driver->getTexture(texture));
  this->rainParticleSystem->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
}


// Registers a click event with the Game instance:
void GameInstance::clickEvent(BorbieInputEvent click) {
  switch(click){
    // if left click
    case BORBIE_LEFT_CLICK:
      // attempt to punch something
      this->punch();
      break;
      // if right click
    case BORBIE_RIGHT_CLICK:
      break;
    default:
      break;
  }
}



/*** PER-FRAME UPDATE METHODS ***/

// called each frame by Game object to upda all of the GameInstance
//  subsystems, including GUI, target selector, and sound.
void GameInstance::update(){
  // update all subsystems
  this->drawGUI();
  this->updateSelector();
  this->audioSystem->updateSound(
      this->camera->getPosition(),
      this->camera->getRotation()
      );
  this->enemies->update();
  this->vehicles->update();
  this->hands->update();

  if((player->getHealth() < 250) && (bgSound!=bgSoundDead))
  {
    bgSound = bgSoundDead; 
    audioSystem->playMusicLoop(bgSound); 
    audioSystem->setMusicVolume(0.2);

  }

  if(player && game)
    if(player->hasExploded())
    {
      float screenHeight = driver->getScreenSize().Height;
      float screenWidth = driver->getScreenSize().Width;

      driver->draw2DImage(
          this->menu,
          rect<s32>(screenWidth/3, screenHeight/3, screenWidth*2/3, screenHeight* 2/3),
          rect<s32>(0, 0,
            this->menu->getSize().Width,
            this->menu->getSize().Height));
  
    }


  // update global (publically available) game timer
  this->currentGameTime = this->timer->getTime();

  // check objects in the update list that need to be updated each frame;
  //  if they are done needing to be updated (their updateTimer function
  //  returns true), then it is removed from the update list and gladly
  //  ignored again.
  for(std::vector<GameObject *>::iterator it = this->updateList.begin();
      it != this->updateList.end(); ++it)
  {
    //std::cout << updateList.size() << std::endl;
    unsigned int retval = (*it)->updateTimers();
    switch(retval){
      case GAME_OBJ_DELETE: // delete object AND remove it from lists
        //  this->vehicles->removeObject(*it);
      case GAME_OBJ_REMOVE_FROM_UPDATE_LIST: // remove object from list
        this->updateList.erase(it);
        it--;
        /*std::cout << "Deleted from update list; new size = "
          << updateList.size() << std::endl;*/
        break;
      case GAME_OBJ_DO_NOTHING: // if do nothing, or unknown, do nothing
      default:
        break;
    }
  }
}

// (private)
// calls update on the hud (called each frame)
void GameInstance::drawGUI(){
  this->hud->drawHud();
}

// (private)
// gets a highlighted scene node if there is one
void GameInstance::updateSelector(){
  // if a highlighted node exists, deselect. If it is still
  //  selected this frame, it will be re-selected below.
  if (highlightedSceneNode) {
    highlightedSceneNode = 0;
  }

  // get a pointer to whichever scene node is targetted (if any)
  ISceneNode * selected = selector->getTarget();
  if (selected){
    highlightedSceneNode = selected;
  }

  // If no vehicle is currently being carried and the right mouse button is
  //  pressed, check if we're currently targetting (highlighting) a vehicle.
  //  If so, then pick it up.
  if (!carriedVehicle && ((BorbiesEventReceiver *)receiver)->isRightMouseDown()){
    VehicleInstance * vehicle =
      (VehicleInstance *)(vehicles->getObject(highlightedSceneNode));
    if(vehicle) { // if vehicle was in fact selected, pick it up
      carriedVehicle = vehicle; // VehicleInstance* (carriedVehicle)
      carriedVehicle->stop(); // remove all animators from the vehicle
      objCarry->pickUp(highlightedSceneNode); // ISceneNode* (highlighted)

      // remove the vehicle's collision so it doesn't make Borbie glitch out
      this->removeCollision(carriedVehicle->getNode()->getTriangleSelector());

      // flag carried vehicle as no longer pickable
      carriedVehicle->getNode()->setID(IDFlag_IsNotPickable);

      // display the target marker on the GUI
      this->hud->setTargetMarkerEnabled(true);

      //set hands invisible
      this->hands->setVisible(false);
    }
  }

  // If we're currently carrying a vehicle, and the left mouse button is
  //  pressed, throw it and break someone's face.
  if (carriedVehicle && !vehicleThrown &&
      ((BorbiesEventReceiver *)receiver)->isLeftMouseDown())
  {
    // get the player's target node
    ISceneNode *target = selector->getThrowTarget();
    //target->setVisible(false);
    if(target)
      std::cout << "Target in sight at distance = " <<
        target->getPosition().getDistanceFrom(carriedVehicle->
            getNode()->getPosition()) << std::endl;

    // throw the selected object at the found target; if target is null
    //  (not found), it will just fly to the maximum distance possible.
    // This will start an animator to fly to the target.
    objCarry->throwObj(target);
    //turn hands back on
    this->hands->setVisible(true);
    vehicleThrown = true;

    // hide the target marker (no longer needed)
    this->hud->setTargetMarkerEnabled(false);
  }

  // update thrownObject (checks if vehicles need to be thrown)
  this->updateThrownObject();
}


// (private)
// Check to see if a vehicle is currently being thrown. If it has been thrown,
//  then it is flying through the air (wheeeeeeeeee!). Once it reaches its
//  destination, make it explode.
void GameInstance::updateThrownObject(){
  // check if a carried vehicle exists and it has been thrown:
  if (carriedVehicle != 0 && vehicleThrown){
    // check if thrown vehicle flew far enough or collided with something
    //if(collided || this->objCarry->objectDoneFlying()){
    if(carriedVehicle->getNode()->getPosition().Y < -50
        || this->objCarry->objectDoneFlying())
    {
      // blow it up
      carriedVehicle->explode();

      // make everything around it take damage:
      // applyExplosionDamage(carriedVehicle);

      // clean up temporaries (make we can pick up more vehicles)
      vehicleThrown = false;
      carriedVehicle = 0;
    }
  }
  }


  // Adds an object to the list of update-required objects, where they will
  //  be updated by the standard update system until they request themselves
  //  to be removed. Thanks Irrlicht.
  void GameInstance::addUpdateObject(GameObject *toUpdate){
    this->updateList.push_back(toUpdate);
  }



  /*** PRIVATE COLLISION METHODS ***/

  // Add a node's Traingle Selector to the global meta selector. Use
  //	irr::scene::ISceneNode->getTriangleSelector() to get one.
  //	Make sure to set it up first with:
  //	smgr->createTriangleSelectorFromBoundingBox(node); (or something)
  void GameInstance::addCollision(irr::scene::ITriangleSelector *selector){
    this->metaTriSelector->addTriangleSelector(selector);
  }

  // Remove a node's Triangle Selector from the global meta selector.
  void GameInstance::removeCollision(irr::scene::ITriangleSelector *selector){
    this->metaTriSelector->removeTriangleSelector(selector);
  }
