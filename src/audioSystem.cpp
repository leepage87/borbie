#include "audioSystem.h"

#include <iostream>


AudioSystem::AudioSystem(){
    this->musicChannel = 0;
    this->ambianceChannel = 0;
    this->playerPosition = { 0.0f, 0.0f, 0.0f };
    
    /*int              key;
    bool             listenerflag = true;
    unsigned int     version;*/
    
    FMOD_RESULT result;
    
    result = FMOD::System_Create(&system);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: System_Create failed." << std::endl;
    
    // TODO: parameters?
    result = system->init(10, FMOD_INIT_NORMAL, 0);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: system init failed." << std::endl;
    
    // TODO: debug - remove
    int numchannels = 0;
    result = system->getHardwareChannels(&numchannels);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: getChannels failed." << std::endl;
    else
        std::cout << "FMOD -- number channels = " << numchannels << std::endl;
}


AudioSystem::~AudioSystem(){

    /*FMOD_RESULT result;
    result = sound1->release();
    ERRCHECK(result);
    result = sound2->release();
    ERRCHECK(result);
    result = sound3->release();
    ERRCHECK(result);*/

    this->system->close();
    this->system->release();
}


// plays the given file in the music channel: if looped flag is true,
//  this will run the track in a repeating loop. Otherwise, it will play
//  once and stop.
void AudioSystem::playMusic(const char *file, bool looped){
    FMOD_RESULT result;
    
    // create the sound from the given file path
    FMOD::Sound *musicSound;
    result = system->createSound(file, FMOD_SOFTWARE, 0, &musicSound);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: createSound failed." << std::endl;
    
    // set looped on or off, depending on parameter
    if(looped)
        result = musicSound->setMode(FMOD_LOOP_NORMAL);
    else
        result = musicSound->setMode(FMOD_LOOP_OFF);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: setMode (sound) failed." << std::endl;
    
    // attempt to play the sound file in the music channel.
    result = system->playSound(FMOD_CHANNEL_FREE, musicSound, 0,
        &(this->musicChannel));
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: playSound failed." << std::endl;
    
    // update FMOD system
    this->system->update();
    
    //result = musicSound->release();
    // TODO: where to delete? memory leak atm? (maybe...)
}


// calls the internal playMusic function with loop set to false
void AudioSystem::playMusic(const char *file){
    this->playMusic(file, false);
}


// calls the internal playMusic function with loop set to true
void AudioSystem::playMusicLoop(const char *file){
    this->playMusic(file, true);
}


// If the music channel is currently playing, stops playback.
//  NOTE: This method DOES NOT remove the sound from memory.
void AudioSystem::stopMusic(){
    // TODO: actually implement this
}































