#include "Actor.h"
#include <Level.h>

Actor::Actor(Level* l, float x_,float y_,float w,float h) {
  level = l;
  x = x_;
  y = y_;
  width = w;
  height = h;
  isDead=false;
}

float Actor::getX1() const {return x-level->getX();}
float Actor::getX2() const {return getX1()+width;}
float Actor::getY1() const {return y-level->getY();}
float Actor::getY2() const {return getY1()+height;}

void Actor::setPosition(float x_, float y_,bool keepLast) {
  x=x_+level->getX();
  y=y_+level->getY();
}
