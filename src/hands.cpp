
#include <iostream>

#include "gameInstance.h"
#include "audioSystem.h"

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;

Hands::Hands(GameInstance * gameInstance){
    this->gameInstance = gameInstance;
    this->camera = gameInstance->getCamera();
    this->smgr = gameInstance->getSceneManager();
    this->audioSystem = gameInstance->getAudioSystem();
    this->lastPunchTime = 0;
    addLeftHand();
    addRightHand();

    //add sounds
    this->punch1 = audioSystem->createSound3d("assets/sounds/soundEffects/punches/punch1.mp3");
    this->punch2 = audioSystem->createSound3d("assets/sounds/soundEffects/punches/punch2.mp3");
    this->punch3 = audioSystem->createSound3d("assets/sounds/soundEffects/punches/punch3.mp3");
    this->punch4 = audioSystem->createSound3d("assets/sounds/soundEffects/punches/punch4.mp3");
    this->punch5 = audioSystem->createSound3d("assets/sounds/soundEffects/punches/punch5.mp3");
    this->punch6 = audioSystem->createSound3d("assets/sounds/soundEffects/punches/punch6.mp3");
}

Hands::~Hands(){
    if (punch1)
        punch1->release();
    if (punch2)
        punch2->release();
    if (punch3)
        punch3->release();
    if (punch4)
        punch4->release();
    if (punch5)
        punch5->release();
    if (punch6)
        punch6->release();
    if (leftHand)
        leftHand->drop();
    if (rightHand)
        rightHand->drop();
}

void Hands::addLeftHand(){
    leftHand = smgr->addMeshSceneNode(smgr->getMesh("assets/models/body/Left_hand.obj"));
    leftHand->setParent(camera);
    leftHand->setPosition(vector3df(-80,-40,100));
    leftHand->setScale(vector3df(10,10,10));
    leftHand->setRotation(vector3df(-70,-90,0));
    leftHand->setID(0);//unselectable
}

void Hands::addRightHand(){
    rightHand = smgr->addMeshSceneNode(smgr->getMesh("assets/models/body/Right_hand.obj"));
    rightHand->setParent(camera);
    rightHand->setPosition(vector3df(80,-40,100));
    rightHand->setScale(vector3df(10,10,10));
    rightHand->setRotation(vector3df(45,90,90));
    rightHand->setID(0);//unselectable
}

void Hands::setVisible(bool value){
    leftHand->setVisible(value);
    rightHand->setVisible(value);
}

void Hands::update(){
    if (rightPunched){
        unsigned int currentTime = gameInstance->getDevice()->getTimer()->getTime();
        if (lastPunchTime - currentTime >=125)
            punchLeft();
    }
}
void Hands::punch(){
    vector3df cameraRot = camera->getRotation();
    cameraRot.Y -=15;
    camera->setRotation(cameraRot);
    lastPunchTime = gameInstance->getDevice()->getTimer()->getTime();
    rightPunched = true;
    //play random punch sound
    punchSound();
}

void Hands::punchLeft(){
    vector3df cameraRot = camera->getRotation();
    cameraRot.Y +=15;
    camera->setRotation(cameraRot);
    rightPunched = false;
}

void Hands::punchSound(){
    int num = Random::randomInt(0, 6);
    switch (num){
        case 0:
            this->audioSystem->playSound3d(punch1, gameInstance->player);         
            break;
        case 1:
            this->audioSystem->playSound3d(punch2, gameInstance->player); 
            break;
        case 2:
            this->audioSystem->playSound3d(punch3, gameInstance->player); 
            break;
        case 3:
            this->audioSystem->playSound3d(punch4, gameInstance->player); 
            break;
        case 4:
            this->audioSystem->playSound3d(punch5, gameInstance->player); 
            break;
        case 5:
            this->audioSystem->playSound3d(punch6, gameInstance->player); 
            break;
    }
}
