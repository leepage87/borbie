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
	IMetaTriangleSelector *metaTriSelector)
{
    // remember pointers to necessary Irrlicht objects
	this->smgr = smgr;
	this->driver = driver;
	this->metaTriSelector = metaTriSelector;
	
	// seed the random number generator (using system time)
	srand(time(NULL));
	
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

// delete all of the buildings in the building list
Buildings::~Buildings(){
	for(std::vector<BuildingInstance *>::iterator it = buildingList.begin();
		it != buildingList.end(); ++it)
	{
		delete (*it);
	}
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
	// TODO: put this in another file. Perhaps the Buildings object should just
	//  have a function generateCity() using the map.
	const int farX = 20000.0f;
	const int farY = 20000.0f;
	std::ifstream mapfile(buildingCoords);
	for(std::string line; getline(mapfile, line); ) {
        if(line.size() == 0) // skip empty lines
            continue;
        else if(line[0] == '#') // skip commented lines (beginning w/ "#")
            continue;
        else {
            // TODO: have some try/catch check in case file is broken
            std::istringstream lineParser(line);
            float coordX, coordY;
            lineParser >> coordX;
            lineParser >> coordY;
            // use coordinates to add the building at specified location
            this->addRandomBuilding(
		        farX * coordX,
		        //BUILDING_GROUND_HEIGHT,
		        50.0f,
		        farY * (coordY)
	        );
            std::cout << "Generated building at " <<
                "x: " << coordX << ", y: " << coordY << std::endl;
        }
    }
}


// Add a building at the given position with a randomized height
//  (provided by the getRandomHeight function) and a texture
//  selected randomly from the textureList std::vector.
// --- (public) ---
void Buildings::addRandomBuilding(
	float xPos, float yPos, float zPos)
{
    // get random height and texture index
    float rHeight = this->getRandomHeight();
    int textureIndex = rand() % this->textureList.size();
    
    // make the building with those parameters and the given position
	this->makeBuilding(textureIndex, rHeight, xPos, yPos, zPos);
}


// Returns a random height between the maximum and minimum heights allowed,
//  with a general bias towards mid-ranged heights.
float Buildings::getRandomHeight(){
    // get random integer between 0 and 99
    /*int randVal = rand() % 100;
    
    // calculate number of possible height values
    int heightRange = BUILDING_MAX_HEIGHT - BUILDING_MIN_HEIGHT;
    int numHeights = heightRange/BUILDING_HEIGHT_DIFF + 1;
    
    // map the randomly generated number to the index
    
    // rand = [0, 1)
    // rand = rand^(1.5) (bias towards 0)
    // x = rand(0, 1)
    // if (x==0): // min-average
    //  bias = 1 - rand
    // elif (x==1): // average-max
    //  bias = 1 + rand
    // bias = [0, 2) with bias towards 1
    
    int scale = 100 / numHeights;
    int selectedIndex = (randVal / scale);
    
    // find the actual height using the randomly found index
    float rHeight = BUILDING_MIN_HEIGHT + BUILDING_HEIGHT_DIFF * selectedIndex;
    std::cout << "HEIGHT: " << rHeight << std::endl;
    return rHeight;*/
    
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
// --- (private) ---
void Buildings::makeBuilding(
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
			BUILDING_WIDTH, height, BUILDING_DEPTH,
			xPos, yPos, zPos,
			texture
		);
	newBuilding->applyCollision(this->metaTriSelector);
	this->buildingList.push_back(newBuilding);
}
