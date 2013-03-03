#ifndef OBJECT_H
#define OBJECT_H

#include <string>
//#include <irrlicht.h>

class object {
  private:
    int health;

  public:
    virtual std::string toString()=0;

    //inline functions
    int getHealth()
    {
      return health; 
    }

    int setHealth(int new_health)
    {
      health=new_health;
    }

};

#endif
