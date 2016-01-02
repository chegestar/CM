#include "Dynamite.h"
#include <Level.h>
#include <Explosion.h>
Dynamite::Dynamite(Level*l, float x_,float y_,C_CODE col) :
  Item(l,x_,y_,l->getWidth(),l->getHeight()) {
  c=col;
}

void Dynamite::blowup() {
  setDead();
  float nx = x+width/2;
  float ny = y+height/2;
  if (x<0&&y<0) {
    Bob* b = level->getBob();
    ny = b->getY1()+b->getHeight()/2+level->getY();
    nx = b->getX1()+b->getWidth()/2+level->getX();
  }
  Explosion* explo = new Explosion(level,nx-level->getWidth()/2,ny-level->getHeight()/2);
  level->addActor(explo);
}
