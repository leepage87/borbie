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
    if(numSpawnPoints == 0){
        std::cout << "No spawn points... enemies not generated." << std::endl;
        return;
        }
    
    for(int i=0; i<STARTING_NUMBER_ENEMIES; ++i){
        // choose a random spawn point
        int spawnIndex = Random::randomInt(numSpawnPoints);
        
        // create the enemy at location of the given spawn point
        this->makeEnemy(
            MapReader::enemySpawnPoints[spawnIndex].X,
            70, // ENEMY_HEIGHT
            MapReader::enemySpawnPoints[spawnIndex].Y);
    }
}


// create a new enemy
void Enemies::makeEnemy(float xPos, float yPos, float zPos){
	//for (int i = 0; i <= 1200; i+=300){
	  Soldier *newSoldier
		  = new Soldier(
			  this->gameInstance,
			  xPos, yPos, zPos
		  );
		  
      newSoldier->applyCollision(this->metaTriSelector);
	  this->addObject(newSoldier);

      /*BigAssSoldier *newBigAssSoldier = new BigAssSoldier(this->gameInstance, 12000, 70, 12000);
      newBigAssSoldier->applyCollision(this->metaTriSelector);
      this->addObject(newBigAssSoldier);
		//}
    */
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
