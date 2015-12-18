#include <Die.h>

#ifndef __FIRE__H__
#define __FIRE__H__

class Bob;

class Fire : public Die {
 public:
  Fire(Level* l, float x, float y);
    
  void render(sf::RenderWindow& window);
};

#endif
