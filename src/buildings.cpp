/*	File: buildings.cpp
 *	Authors: idk your names
 *
 *	Description: this file contains the class declaration of the
 *	buildings list object. The building list object contains a
 *	function for constructing all buildings and placing them into the
 *	scene automatically.
 */

#include "buildings.h"

// include cpp library headers for random number generation
// TODO: make the random generator global (static object)
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>       /* pow */

// include cpp library headers for reading the building coordinate file
#include <fstream>
#include <string>
#include <iostream>
#include <istream>
#include <sstream>

using namespace irr;
using namespace scene;
using namespace video;


// CONSTRUCTOR: initializes the list of building textures as they will
//  be applied to each generated building. Sets up pointers to keep track
//  of Irrlicht objects, and also seeds the random generator using system time.
Buildings::Buildings(
	ISceneManager *smgr,
	IVideoDriver *driver,
	IrrlichtDevice *device,
	IMetaTriangleSelector *metaTriSelector,
	GameInstance *gameInstance)
	//passing these to supah constructah:
	: ObjectList(smgr, driver, device, metaTriSelector, gameInstance)
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
}


// Build the city using the given building coordinates file path,
//  adding a randomly sized building at each point as dictated
//  by the loaded file.
// TODO: return int that can return error codes if file failed to load,
//  file data is inappropriate, etc.
// --- (public) ---
void Buildings::generateBuildings(const char *buildingCoords){
    
	/* Positions explained:
	 *  x: 0 to 20000  0 is RIGHT edge of texture
	 *  y: height (~500 is slightly over ground level)
	 *  z: 0 to 20000  0 is TOP edge of texture
	 *
	 *  10000 is half-way; (10000, 10000) = center of texture
	 */
	
    // read in the map building coordinate file
    // TODO: adapt to support trees, lamps, and other objects, too
	const int farX = 20400.0f;
	const int farY = 20400.0f;//19840.0f;
	const int xOffset = -190;
	const int yOffset = -190; // TODO: what the hell?
	std::ifstream mapfile("assets/map/coords.bor");
	if(mapfile.fail()){
	    std::cerr << "ERROR: Cannot open map file." << std::endl;
	    return;
	}
	for(std::string line; getline(mapfile, line); ) {
        if(line.size() == 0) // skip empty lines
            continue;
        else if(line[0] == '#') // skip commented lines (beginning w/ "#")
            continue;
        else if(line[0] != 'b'){ // skip lines that are not building coordinates
            std::cout << "Non-building ignored." << std::endl; // TODO - remove this print
            continue;
        }
        else {
            // try to parse the line into two floats
            std::istringstream lineParser(line);
            // ignore first thing (the 'b')
            std::string ignore;
            lineParser >> ignore;
            // try to read the two floats
            float coordX, coordY;
            lineParser >> coordX;
            lineParser >> coordY;
            // if something failed, don't bother making the building
            if(lineParser.fail()){
                std::cerr << "ERROR: Invalid line in map file:" << std::endl
                          << "       " << line << std::endl;
                continue;
            }
            // use coordinates to add the building at specified location
            this->addRandomBuilding(
		        (farX * coordX) + xOffset,
		        //BUILDING_GROUND_HEIGHT,
		        50.0f,
		        (farY * coordY) + yOffset
	        );
            std::cout << "Generated building at " <<
                "x: " << coordX << ", y: " << coordY << std::endl;
        }
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
    int textureIndex = rand() % this->textureList.size();
    
    // make the building with those parameters and the given position
	return this->makeBuilding(textureIndex, rHeight, xPos, yPos, zPos);
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
    int textureIndex, float height,
	float xPos, float yPos, float zPos)
{
    // create texture, w, h, d based on building type
	ITexture *texture =
	    this->driver->getTexture(this->textureList[textureIndex]);
	
	// create the new building objects, make it apply its collision
	//  to the global meta, and add it to the building list
	BuildingInstance *newBuilding
		= new BuildingInstance(
			this->smgr,
			this->driver,
			this->device,
			this->gameInstance,
			BUILDING_WIDTH, height, BUILDING_DEPTH,
			xPos, yPos, zPos,
			texture
		);
	newBuilding->applyCollision(this->metaTriSelector);
	this->addObject(newBuilding);
	
	return newBuilding;
}
