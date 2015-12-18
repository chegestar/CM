#include <Mover.h>
#include <Die.h>

#ifndef __ENEMY__H__
#define __ENEMY__H__

class Bob;

class Enemy : public Die,public Mover {
 public:
  Enemy(Level* l, float x, float y, float w, float h);
    
  virtual void act();
  void render(sf::RenderWindow& window);
};

#endif
