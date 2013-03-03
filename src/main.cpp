/* CIS 395 Spring 2013 Irrlicht Template File

   Programmer:
*/

#include <irrlicht.h>

/*
  Standard Irrlicht namespaces
*/
using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

// Run with dynamic linking on Win32 by starting main() (rather than WinMain)
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

/* 
   Super-simple event receiver; remove for more complicated programs.
*/
class MyEventReceiver : public IEventReceiver {
public:
  // This is the one method that we have to implement
  virtual bool OnEvent(const SEvent& event) {
    // Remember whether each key is down or up
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
      KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    
    return false;
  }

  // This is used to check whether a key is being held down
  virtual bool IsKeyDown(EKEY_CODE keyCode) const {
    return KeyIsDown[keyCode];
  }
	
  MyEventReceiver() {
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
      KeyIsDown[i] = false;
  }

private:
  // We use this array to store the current state of each key
  bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

int main() {
  MyEventReceiver receiver; 

  IrrlichtDevice *device =
    createDevice(video::EDT_OPENGL,          // Video driver to use
                 dimension2d<u32>(640, 480), // Dimensions of window
                 32,                         // Bit-depth
                 false,                      // Full screen
                 false,                      // Stencil buffer
                 false,                      // Vsync
                 &receiver);                 // Pointer to IEventReceiver

  if (!device)
    return 1;

  device->setWindowCaption(L"<Window Title Text Here>");

  /* Cache pointers to the VideoDriver, SceneManager, and
     GUIEnvironment in local variables. */
  IVideoDriver* driver = device->getVideoDriver();
  ISceneManager* smgr = device->getSceneManager();
  IGUIEnvironment* guienv = device->getGUIEnvironment();

  guienv->addStaticText(L"<GUI Text to Render>",
                        rect<s32>(10,10,260,22), true);


  while(device->run()) {
    driver->beginScene(true, true, SColor(255,100,101,140));
    
    smgr->drawAll();
    guienv->drawAll();

    driver->endScene();
  }

  device->drop();
  
  return 0;
}

