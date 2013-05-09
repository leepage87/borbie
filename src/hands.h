/*********************************************************************
 * File:     hands.h
 * Authors:  Richard Teammco, Lee Page, Jonathan Miodownik
 * Function: This is the header file for hands.cpp
 *********************************************************************/

#ifndef HANDS_H
#define HANDS_H

// include irrlicht

#include <irrlicht.h>

#include"random.h"

//GameInstance and AudioSystem are used
class GameInstance;
class AudioSystem;

class Hands {
    protected:
    GameInstance *gameInstance;
    irr::scene::ISceneManager *smgr;
    irr::scene::ICameraSceneNode *camera;
    AudioSystem *audioSystem;

    private:
    irr::scene::ISceneNode *leftHand;
    irr::scene::ISceneNode *rightHand;
    bool rightPunched;
    unsigned int lastPunchTime;

    //sounds
    SoundClip *punch1;
	SoundClip *punch2;
	SoundClip *punch3;
    SoundClip *punch4;
    SoundClip *punch5;
    SoundClip *punch6;
    SoundClip *punchMiss;
    //load the models
    void addLeftHand();
    void addRightHand();
    //methods that are called from this class
    //after a call to punch()
    void punchSound();
    void punchLeft();
    

    public:
    Hands(GameInstance *gameInstance);
    ~Hands();
    void setVisible(bool value);   
    void punch();
    void update();
};

#endif
