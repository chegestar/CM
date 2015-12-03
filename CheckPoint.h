
#include "Actor.h"

#ifndef __CHECKPOINT__H__
#define __CHECKPOINT__H__

class CheckPoint : public Actor {
 public:
 CheckPoint(Level* l, float x_,float y_) : Actor(l,x_,y_,32,32) {};

  void render(sf::RenderWindow& window);

 
};

#endif
