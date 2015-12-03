#include "Mover.h"
#include <Level.h>


Mover::Mover(Level* l, float x_,float y_,float w,float h) : Actor(l,x_,y_,w,h) {
  lastx=lasty=0;
}

void Mover::act() {
  lastx = getX1();
  lasty = getY1();
}

float Mover::getMovementCorrectionX(float speed) {return speed*level->getWidth()/32;}
float Mover::getMovementCorrectionY(float speed) {return speed*level->getHeight()/32;}


