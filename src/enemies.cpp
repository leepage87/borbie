/*********************************************************************
 * File:     enemies.cpp
 * Authors:  Richard Teammco, Lee Page, Jonathan Miodownik
 * Function: This class generates all the soldiers in the game and 
 *           creates a list containing their pointers, allowing us to
 *           call each of their updatePosition() methods.
 *********************************************************************/

#include "enemies.h"
#include "random.h"
#include "mapReader.h"
#include "gameInstance.h"

#include <iostream> // TODO: debug (remove)

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;


const unsigned int STARTING_NUMBER_ENEMIES = 10;
const unsigned int MAX_NUMBER_ENEMIES = 1000;

/*********************************************************************
 * Creates a list object to hold references to all the enemies
 * in the game
 * Param: metaTriSelector a pointer to our collision handler
 * Param: gameInstance the gameInstance containing all relevant
 *        pointers
 *********************************************************************/
Enemies::Enemies(
	IMetaTriangleSelector *metaTriSelector,
	GameInstance *gameInstance)
	// call super ObjectList constructor first:
	: ObjectList(metaTriSelector, gameInstance)
{
    this->maxNumberEnemies = STARTING_NUMBER_ENEMIES;
}

/*********************************************************************
 * Generate a default amount of enemies which start moving towards
 * borbie. If she wrecks stuff, more will spawn.
 *********************************************************************/
void Enemies::generateObjects(){
    MapReader *mapReader = this->gameInstance->getMapReader();
    int numSpawnPoints = mapReader->enemySpawnPoints.size();
    if(numSpawnPoints == 0)
        return;
    
    for(int i=0; i<this->maxNumberEnemies; ++i){
        // randomly spawn an enemy at some random spawn point
        this->createRandomEnemy();
    }
}

/*********************************************************************
 * Increase the maximum number of enemies that can spawn at any given
 * point in time by the given amount.
 *********************************************************************/
void Enemies::addMaxEnemies(unsigned int amount){
    this->maxNumberEnemies += amount;
}

/*********************************************************************
 * Randomly creates an enemy near a randomly selected spawn point (exact
 * position is also randomized by an offset). The enemy created is also
 * random by a weighed percentage.
 *********************************************************************/
void Enemies::createRandomEnemy(){
    MapReader *mapReader = this->gameInstance->getMapReader();
    
    // get number of available spawn points: make sure there are some to spawn
    //  enemies from.
    int numSpawnPoints = mapReader->enemySpawnPoints.size();
    if(numSpawnPoints == 0)
        return;
        
    // choose a random spawn point
    int spawnIndex = Random::randomInt(numSpawnPoints);
        
    // determine enemy type: 10% chance to get big ass solider, otherwise
    //  normal soldier
    EnemyType type;
    if(Random::randomInt(10) == 0)
        type = ENEMY_TYPE_BIG_ASS_SOLDIER;
    else
        type = ENEMY_TYPE_SOLDIER;
    
    // choose a random location around the exact spawn point
    int xOffset = Random::randomInt(2000) - 1000;
    int yOffset = Random::randomInt(2000) - 1000;
    // create the enemy at location of the given spawn point
    this->makeEnemy(
        mapReader->enemySpawnPoints[spawnIndex].X + xOffset,
        70, // ENEMY_HEIGHT
        mapReader->enemySpawnPoints[spawnIndex].Y + yOffset,
        type);
}

/*********************************************************************
 * Create one enemy
 * Param: xPos The X position the enemy will be generated at
 * Param: yPos The Y position the enemy will be generated at
 * Param: zPos The Z position the enemy will be generated at
 * Param: type The type of enemy that will be generated
 *********************************************************************/
void Enemies::makeEnemy(float xPos, float yPos, float zPos, EnemyType type){

    // create the enemy based on type given
    GameObject *enemy;
    switch(type){
        case ENEMY_TYPE_BIG_ASS_SOLDIER: // if big ass soldier
            enemy = new BigAssSoldier(this->gameInstance, xPos, yPos, zPos);
            break;
        case ENEMY_TYPE_SOLDIER: // if regular solider or unknown type
        default:
            enemy = new Soldier(this->gameInstance, xPos, yPos, zPos);
            break;
    }
   
    enemy->applyCollision(this->metaTriSelector);
	this->addObject(enemy);
}

/*********************************************************************
 * Call update on each of the enemies in the list
 *********************************************************************/
void Enemies::update(){
    // if number of enemies is below the current limit, make moar!
    while(this->objList.size() < this->maxNumberEnemies){
        this->createRandomEnemy();
        std::cout << "NEW ENEMY CREATED" << std::endl;
    }
    
    // update each enemy individually if they are not blown up yet
    int numObjs = objList.size();
    for(int j=0; j<numObjs; ++j){
	    if(objList[j]){
		    if(objList[j]->getNode()->isVisible())
            	((Soldier*)objList[j])->update();
		}	
	}
}
