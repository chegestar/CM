#include "FakeExit.h"
#include <Level.h>
FakeExit::FakeExit(Level*l, float x_,float y_, float nx, float ny) :
  Switch(l,x_,y_,32,32){
  newx=nx;
  newy = ny;
  texture_keys.push_back("exit");
}


int FakeExit::activate() {
  Bob* b = level->getBob();
  b->setPosition(newx,newy);
  return 0;
}
