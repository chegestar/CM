#include <Die.h>

#ifndef __LAVA__H__
#define __LAVA__H__

class Bob;

class Lava : public Die {
 public:
  Lava(Level* l, float x, float y);
  
  bool hitBob(Bob* b);

  void render(sf::RenderWindow& window);
};

#endif
