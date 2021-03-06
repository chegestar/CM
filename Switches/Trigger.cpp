#include "Trigger.h"
#include <Level.h>
#include <Dynamite.h>
#include <Bob.h>
Trigger::Trigger(Level*l, float x_,float y_,C_CODE col) :
  Switch(l,x_,y_,l->getWidth(),l->getHeight()){
  c = col;
  texture_keys.push_back(std::vector<std::string>(1,"trigger_off"));
  texture_keys.push_back(std::vector<std::string>(1,"trigger_on"));
}


int Trigger::activate() {
  level->getBob()->removeDynamite(c);
  for (unsigned int i=0;i<sticks.size();i++) {
    sticks[i]->blowup();
  }
  sticks.clear();
  texture_set=1;
  return 0;
}
