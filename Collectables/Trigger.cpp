#include "Trigger.h"
#include <Level.h>
#include <Dynamite.h>
Trigger::Trigger(Level*l, float x_,float y_) :
  Switch(l,x_,y_,l->getWidth(),l->getHeight()){
}


int Trigger::activate() {
  for (unsigned int i=0;i<sticks.size();i++) {
    sticks[i]->blowup();
  }
  setDead();
  return 0;
}
