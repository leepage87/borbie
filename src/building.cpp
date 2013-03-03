#include "object.h"
#include <iostream>

using namespace std;

class building : public object {
  string toString()
  {
    return "building";
  }
};


int main()
{
  building *b = new building();

  b->setHealth(5);
  cout<< b->getHealth() << endl;
}
