#include "Switch.h"
#include <utilities.h>
#include <Level.h>

Switch::Switch(Level* l, float x_, float y_, float w, float h) : 
  Actor(l,x_,y_,w,h) {
  shape = new sf::CircleShape(width/2);

}

