#include "Die.h"
#include <Bob.h>
#include <utilities.h>
#include <Level.h>
#include <Enemy.h>
Die::Die(Level* l, float x, float y, float w, float h) : 
  Actor(l,x,y,w,h) {


}
bool Die::hitBob(Bob* b) {
  return isRectangularHit(b,this);
    
}

void Die::act() {
  if (hitBob(level->getBob())) {
    
    if (!level->getBob()->die()&&dynamic_cast<Enemy*>(this))
      setDead();
  }
}

