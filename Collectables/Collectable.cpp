#include "Collectable.h"
#include <utilities.h>
#include <Level.h>

Collectable::Collectable(Level* l, float x_, float y_, float w, float h) : 
  Switch(l,x_,y_,w,h) {
}

int Collectable::activate() {
  isDead=true;
  return 0;
}
