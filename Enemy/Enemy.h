#include <Mover.h>

#ifndef __ENEMY__H__
#define __ENEMY__H__

class Bob;

class Enemy : public Mover {
 private:

 public:
  Enemy(Level* l, float x, float y, float w, float h) : Actor(l,x,y,w,h), Mover(l,x,y,w,h) {};
  
  virtual bool hitBob(Bob* b);
  
  virtual void act();
  void render(sf::RenderWindow& window);
};

#endif
