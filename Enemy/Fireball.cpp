#include "Fireball.h"
#include <Level.h>

Fireball::Fireball(Level* l, float x, float y,bool d) :
  Actor(l,x,y,32*4.0/5,32*4.0/5), Spider(l,x,y,d) {}
