#ifndef HANDS_H
#define HANDS_H

// include irrlicht

#include <irrlicht.h>

#include"random.h"

//GameInstance and AudioSystem is used
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

    void addLeftHand();
    void addRightHand();
    void punchSound();
    void punchLeft();
    

    public:
    Hands(GameInstance *gameInstance);

    void setVisible(bool value);   
    void punch();
    void update();
};

#endif
