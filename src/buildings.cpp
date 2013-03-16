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
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

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


// build the city using the given building coordinates file path
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
		        BUILDING_GROUND_HEIGHT,
		        farY * (coordY)
	        );
            std::cout << "Generated building at " <<
                "x: " << coordX << ", y: " << coordY << std::endl;
        }
    }
}


// public addBuilding: add a random building at the given position.
void Buildings::addRandomBuilding(
	float xPos, float yPos, float zPos)
{
    // generate random height
    int rHeight = rand() % 10 + 1;
    rHeight = rHeight * 5 + 20.0;
    
    // get a random texture index from the texture list
    int textureIndex = rand() % this->textureList.size();
    
	this->makeBuilding(textureIndex, rHeight, xPos, yPos, zPos);
}


// make a building with the given texture and height value
void Buildings::makeBuilding(
    int textureIndex, float height,
	float xPos, float yPos, float zPos)
{
    // create texture, w, h, d based on building type
	ITexture *texture =
	    this->driver->getTexture(this->textureList[textureIndex]);
	float width = 40.0f;
	float depth = 40.0f;
	
	BuildingInstance *newBuilding
		= new BuildingInstance(
			this->smgr,
			width, height, depth,
			xPos, yPos, zPos,
			texture
		);
	
	newBuilding->applyCollision(this->metaTriSelector);
	
	this->buildingList.push_back(newBuilding);
}
