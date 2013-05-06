/*	File: enemy.cpp
 *	Authors: idk your names
 *
 *	Description: ENEMIES!
 */

#include "enemies.h"
#include "random.h"
#include "mapReader.h"
#include <iostream> // TODO: debug (remove)
using namespace std;

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;


const unsigned int STARTING_NUMBER_ENEMIES = 10;
const unsigned int MAX_NUMBER_ENEMIES = 1000;

// Create the enemies list object
Enemies::Enemies(
	IMetaTriangleSelector *metaTriSelector,
	GameInstance *gameInstance)
	// call super ObjectList constructor first:
	: ObjectList(metaTriSelector, gameInstance)
{
    this->maxNumberEnemies = STARTING_NUMBER_ENEMIES;
}


// Generate a default amount of enemies which start moving towards
//  borbie. If she wrecks stuff, more will spawn.
void Enemies::generateObjects(){
    int numSpawnPoints = MapReader::enemySpawnPoints.size();
    if(numSpawnPoints == 0)
        return;
    
    for(int i=0; i<this->maxNumberEnemies; ++i){
        // randomly spawn an enemy at some random spawn point
        this->createRandomEnemy();
    }
}


// randomly creates an enemy near a randomly selected spawn point (exact
//  position is also randomized by an offset). The enemy created is also
//  random by a weighed percentage.
void Enemies::createRandomEnemy(){
    // get number of available spawn points: make sure there are some to spawn
    //  enemies from.
    int numSpawnPoints = MapReader::enemySpawnPoints.size();
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
        MapReader::enemySpawnPoints[spawnIndex].X + xOffset,
        70, // ENEMY_HEIGHT
        MapReader::enemySpawnPoints[spawnIndex].Y + yOffset,
        type);
}


// create a new enemy
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


// updates the enemies
void Enemies::update(){
    // TODO - fix this by having game objects able to remove themselves -
    //  this might be a big in Buildings also BTW
    /*for(int i=0; i<this->objList.size(); ++i){
        if(this->objList[i]->hasExploded()){
            this->deleteObject(this->objList[i]);
            i--;
        }
    }*/
    
    // if number of enemies is below the current limit, make moar!
    while(this->objList.size() < this->maxNumberEnemies){
        this->createRandomEnemy();
        std::cout << "NEW ENEMY CREATED" << std::endl;
    }
    
    int numObjs = objList.size();
    for(int j=0; j<numObjs; ++j){
	    if(objList[j]){
		    if(objList[j]->getNode()->isVisible())
            	((Soldier*)objList[j])->updatePosition();
		}	
	}
}
