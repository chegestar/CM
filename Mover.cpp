#include "Mover.h"
#include <Level.h>


Mover::Mover(Level* l, float x_,float y_,float w,float h) : Actor(l,x_,y_,w,h) {
  lastx=lasty=0;
}

float Mover::getLastX1() const {return getBoundX1()+lastx-x;}
float Mover::getLastX2() const {return getBoundX2()+lastx-x;}
float Mover::getLastY1() const {return getBoundY1()+lasty-y;}
float Mover::getLastY2() const {return getBoundY2()+lasty-y;}


void Mover::act() {
  lastx = x;
  lasty = y;
}

float Mover::getMovementCorrectionX(float speed) {return speed*level->getWidth()/32;}
float Mover::getMovementCorrectionY(float speed) {return speed*level->getHeight()/32;}


