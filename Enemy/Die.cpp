#include "Die.h"
#include <Bob.h>
#include <utilities.h>
#include <Level.h>

Die::Die(Level* l, float x, float y, float w, float h) : 
  Actor(l,x,y,w,h) {


}
bool Die::hitBob(Bob* b) {
  return isRectangularHit(b,this);
    
}

void Die::act() {
  if (hitBob(level->getBob())) {
    level->getBob()->die();
  }
}

