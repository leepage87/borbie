/*	File: vehicles.cpp
 *	Authors: idk your names
 *
 *	Description: this file contains the class declaration of the
 *	vehicles list object. The vehicles list object contains a
 *	function for constructing all vehicles and placing them into the
 *	scene automatically.
 */

#include "vehicles.h"

// include cpp library headers for random number generation
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace irr;
using namespace scene;
using namespace video;


Vehicles::Vehicles(
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
	//change this to model list
	/*this->textureList.push_back("assets/textures/buildings/building1.png");
	this->textureList.push_back("assets/textures/buildings/building2.jpg");
	this->textureList.push_back("assets/textures/buildings/building3.jpg");
	this->textureList.push_back("assets/textures/buildings/building4.jpg");
	this->textureList.push_back("assets/textures/buildings/building5.jpg");
	this->textureList.push_back("assets/textures/buildings/building6.jpg");
*/
}

// delete all of the buildings
Vehicles::~Vehicles(){
	for(std::vector<VehicleInstance *>::iterator it = vehicleList.begin();
		it != vehicleList.end(); ++it)
	{
		delete (*it);
	}
}


// public addBuilding: add a random building at the given position.
void Vehicles::addRandomVehicle(
	float xPos, float yPos, float zPos)
{
    // generate random height
    //int rHeight = rand() % 10 + 1;
    //rHeight = rHeight * 5 + 20.0;

    //change this to models
    // get a random texture index from the texture list
    //int textureIndex = rand() % this->textureList.size();
    
	this->makeVehicle(xPos, yPos, zPos);
}


// make a vehicle with the given texture and height value
void Vehicles::makeVehicle(
	float xPos, float yPos, float zPos)
{
    // create texture, w, h, d based on building type
	/*ITexture *texture =
	    this->driver->getTexture(this->textureList[textureIndex]);
	float width = 40.0f;
	float depth = 40.0f;
	*/

	VehicleInstance *newVehicle
		= new VehicleInstance(
			this->smgr,
			xPos, yPos, zPos
		);
	
	newVehicle->applyCollision(this->metaTriSelector);
	
	this->vehicleList.push_back(newVehicle);
}
