#include "stdafx.h"
#include "Mover.h"



Mover::Mover(Level* l, float x_,float y_,float w,float h) : Actor(l,x_,y_,w,h) {
  lastx=lasty=0;
}

void Mover::act() {
  lastx = getX1();
  lasty = getY1();
}

