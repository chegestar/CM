#include "Life.h"
#include <utilities.h>
#include <Level.h>
#include <Bob.h>

Life::Life(Level* l, float x_, float y_) : 
  Collectable(l,x_,y_,l->getWidth(),l->getHeight()) {
  texture_keys.push_back("life");
}

int Life::activate() {
  Collectable::activate();
  level->getBob()->earnLife();
  return 10;
}
