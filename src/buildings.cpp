/*	File: buildings.cpp
 *	Authors: idk your names
 *
 *	Description: this file contains the class declaration of the
 *	buildings list object. The building list object contains a
 *	function for constructing all buildings and placing them into the
 *	scene automatically.
 */

#include "buildings.h"
#include "mapReader.h"

// include cpp library headers for random number generation
// TODO: make the random generator global (static object)
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>       /* pow */

#include <iostream>

using namespace irr;
using namespace scene;
using namespace video;


// CONSTRUCTOR: initializes the list of building textures as they will
//  be applied to each generated building. Sets up pointers to keep track
//  of Irrlicht objects, and also seeds the random generator using system time.
Buildings::Buildings(
	IMetaTriangleSelector *metaTriSelector,
	GameInstance *gameInstance)
	//passing these to supah constructah:
	: ObjectList(metaTriSelector, gameInstance)
{
	// seed the random number generator (using system time)
	srand(time(NULL)); // TODO - do this elsewhere
	
	// populate the texture list
	this->textureList.push_back("assets/textures/buildings/building1.png");
	this->textureList.push_back("assets/textures/buildings/building2.jpg");
	this->textureList.push_back("assets/textures/buildings/building3.jpg");
	this->textureList.push_back("assets/textures/buildings/building4.jpg");
	this->textureList.push_back("assets/textures/buildings/building5.jpg");
	this->textureList.push_back("assets/textures/buildings/building6.jpg");
	this->textureList.push_back("assets/textures/buildings/building7.jpg");
	this->textureList.push_back("assets/textures/buildings/building8.jpg");
	this->textureList.push_back("assets/textures/buildings/building9.jpg");
	this->textureList.push_back("assets/textures/buildings/building10.jpg");
	this->textureList.push_back("assets/textures/buildings/building11.jpg");
	this->textureList.push_back("assets/textures/buildings/building12.jpg");
	this->textureList.push_back("assets/textures/buildings/building13.png");
	this->textureList.push_back("assets/textures/buildings/building14.jpg");
	this->textureList.push_back("assets/textures/buildings/building15.jpg");
	this->textureList.push_back("assets/textures/buildings/building16.jpg");
	this->textureList.push_back("assets/textures/buildings/building17.jpg");
	this->textureList.push_back("assets/textures/buildings/RoofOp1.jpg");
	this->textureList.push_back("assets/textures/buildings/RoofOp2.jpg");
	this->textureList.push_back("assets/textures/buildings/RoofOp3.jpg");
	
}


// Build the city using the given building coordinates from the MapReader,
//  adding a randomly sized building at each point as dictated by the
//  coordinate list.
// --- (public) ---
void Buildings::generateBuildings(){
    // read in the map building coordinate file
    for(std::vector<Point>::iterator it = MapReader::buildingCoords.begin();
		it != MapReader::buildingCoords.end(); ++it)
	{
        this->addRandomBuilding((*it).x, BUILDING_GROUND_HEIGHT, (*it).y);
        std::cout << "Generated building at " <<
            "x: " << (*it).x << ", y: " << (*it).y << std::endl;
    }
}


// Add a building at the given position with a randomized height
//  (provided by the getRandomHeight function) and a texture
//  selected randomly from the textureList std::vector.
// RETURNS a pointer to the builing object created
// --- (public) ---
BuildingInstance* Buildings::addRandomBuilding(
	float xPos, float yPos, float zPos)
{
    // get random height and texture index
    float rHeight = this->getRandomHeight();
    int textureIndex = rand() % (this->textureList.size()-3);
    int topTexture = (rand()%3) +17;
    
    // make the building with those parameters and the given position
	return this->makeBuilding(textureIndex, topTexture, rHeight, xPos, yPos, zPos);
}


// Returns a random height between the maximum and minimum heights allowed,
//  with a general bias towards mid-ranged heights. The bias and all height
//  restriction constants can be adjusted in the buildings.h file.
float Buildings::getRandomHeight(){
    // generate a random number
    int randNum = rand() % 100000; // 0 to 99999
    float randf = randNum / 100000.0; // 0 to .99999
    
    // scew the random value (scaled between 0 and 0.5)
    float adjusted = (pow(randf, BUILDING_HEIGHT_BIAS)) / 2.0;
    
    // decide randomly whether or not the building is taller or
    //  smaller than average, and calculate bias outcome between 0 and 1
    int selector = rand() % 2; // 0 or 1
    float bias = 0.f;
    if(selector == 0)
        bias = 0.5 - adjusted;
    else
        bias = 0.5 + adjusted;


    // do the actual building height calculations based on the random bias:
    
    // find number of possible height partitions based on constants 
    const int heightRange = BUILDING_MAX_HEIGHT - BUILDING_MIN_HEIGHT;
    int numHeights = (heightRange / BUILDING_HEIGHT_DIFF) + 1;
    
    // use the bias to determine a height index
    int selIndex = (int)(bias * numHeights);
    
    // scale height index and return value
    float height = BUILDING_MIN_HEIGHT + (BUILDING_HEIGHT_DIFF * selIndex);
    return height;
}


// Make a building with the given texture and height value. This function
//  adds the buildings collision triangles to the global triangle selector
//  for global collision.
// RETURNS the building object created.
// --- (private) ---
BuildingInstance* Buildings::makeBuilding(
    int textureIndex, int topTexture, float height,
	float xPos, float yPos, float zPos)
{
    // create texture, w, h, d based on building type
	ITexture *texture =
	    this->driver->getTexture(this->textureList[textureIndex]);
	ITexture *roofTexture =
 	    this->driver->getTexture(this->textureList[topTexture]);
	
	// create the new building objects, make it apply its collision
	//  to the global meta, and add it to the building list
	BuildingInstance *newBuilding
		= new BuildingInstance(
			this->gameInstance,
			BUILDING_WIDTH, height, BUILDING_DEPTH,
			xPos, yPos, zPos,
			texture, roofTexture
		);
	newBuilding->applyCollision(this->metaTriSelector);
	this->addObject(newBuilding);
	
	return newBuilding;
}
