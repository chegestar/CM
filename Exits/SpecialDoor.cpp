#include "SpecialDoor.h"
#include <Level.h>

SpecialDoor::SpecialDoor(Level* l, float x_,float y_) : 
  Exit(l,x_,y_) {
  texture_keys.clear();
  std::vector<std::string> keys;
  for (int i=0;i<6;i++) {
    char key[20];
    sprintf(key,"special_door_%d",i);
    keys.push_back(key);
  }
  texture_keys.push_back(keys);
};

