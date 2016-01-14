#include "Die.h"
#include <Bob.h>
#include <utilities.h>
#include <Level.h>
#include <Enemy.h>
Die::Die(Level* l, float x, float y, float w, float h) : 
  Actor(l,x,y,w,h) {


}
bool Die::hitBob(Bob* b) {
  return hitTest(b,this);
    
}

void Die::act() {
  Bob* b = level->getBob();
  int posc = getX1()/level->getWidth();
  int posr = getY1()/level->getHeight();
  int bobc = b->getX1()/level->getWidth();
  int bobr = b->getY1()/level->getHeight();
  if (abs(posc-bobc)<4&&abs(posr-bobr)<4)
    if (hitBob(b)) {
      
      if (!level->getBob()->die()&&dynamic_cast<Enemy*>(this))
        setDead();
    }
}

