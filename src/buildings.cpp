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
#include "directoryReader.h"
#include "gameInstance.h"
#include "random.h"

// include cpp library headers for random building sizing
#include <math.h> // pow function
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
    MapReader *mapReader = this->gameInstance->getMapReader();
    
    // populate building texture list with all available file names
    DirectoryReader::getDirectoryFiles(
        mapReader->mapTextureDirectory, // relative path
        this->textureList, "building"); // e.g. "building1.jpg"
  
    // populate roof texture list with all available file names
    DirectoryReader::getDirectoryFiles(
        mapReader->mapTextureDirectory,  // relative path
        this->roofTextures, "Roof");     // e.g. "RoofOp1.jpg"
}


// Build the city using the given building coordinates from the MapReader,
//  adding a randomly sized building at each point as dictated by the
//  coordinate list.
// --- (public) ---
void Buildings::generateObjects(){
    MapReader *mapReader = this->gameInstance->getMapReader();
    
    // read in the map building coordinate file
    for(std::vector<Point>::iterator it = mapReader->buildingCoords.begin();
		it != mapReader->buildingCoords.end(); ++it)
	{
        this->addRandomBuilding((*it).X, BUILDING_GROUND_HEIGHT, (*it).Y);
        std::cout << "Generated building at " <<
            "x: " << (*it).X << ", y: " << (*it).Y << std::endl;
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
    int textureIndex = Random::randomInt(this->textureList.size());
    int topTexture = Random::randomInt(this->roofTextures.size());
    
    // make the building with those parameters and the given position
	return this->makeBuilding(textureIndex, topTexture, rHeight, xPos, yPos, zPos);
}


// Returns a random height between the maximum and minimum heights allowed,
//  with a general bias towards mid-ranged heights. The bias and all height
//  restriction constants can be adjusted in the buildings.h file.
float Buildings::getRandomHeight(){
    // get a random number between 0 and 1 (excluding 1)
    float randf = Random::randomFloat();
    
    // scew the random value (scaled between 0 and 0.5)
    float adjusted = (pow(randf, BUILDING_HEIGHT_BIAS)) / 2.0;
    
    // decide randomly whether or not the building is taller or
    //  smaller than average, and calculate bias outcome between 0 and 1
    int selector = Random::randomInt(2); // 0 or 1
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
	    this->driver->getTexture(this->textureList[textureIndex].c_str());
	ITexture *roofTexture =
 	    this->driver->getTexture(this->roofTextures[topTexture].c_str());
	
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
