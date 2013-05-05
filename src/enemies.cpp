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
{}


// Generate a default amount of enemies which start moving towards
//  borbie. If she wrecks stuff, more will spawn.
void Enemies::generateObjects(){
    int numSpawnPoints = MapReader::enemySpawnPoints.size();
    if(numSpawnPoints == 0)
        return;
    
    for(int i=0; i<STARTING_NUMBER_ENEMIES; ++i){
        // choose a random spawn point
        int spawnIndex = Random::randomInt(numSpawnPoints);
        
        // determine enemy type: 10% chance to get big ass solider, otherwise
        //  normal soldier
        EnemyType type;
        if(Random::randomInt(10) == 0)
            type = ENEMY_TYPE_BIG_ASS_SOLDIER;
        else
            type = ENEMY_TYPE_SOLDIER;
        
        // create the enemy at location of the given spawn point
        this->makeEnemy(
            MapReader::enemySpawnPoints[spawnIndex].X,
            70, // ENEMY_HEIGHT
            MapReader::enemySpawnPoints[spawnIndex].Y,
            type);
    }
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
    int numObjs = objList.size();
    for(int j=0; j<numObjs; ++j){
	    if(objList[j]){
		    if(objList[j]->getNode()->isVisible())
            	((Soldier*)objList[j])->updatePosition();
		}	
	}
}
