#include <Die.h>

#ifndef __LAVA__H__
#define __LAVA__H__

class Bob;

class Lava : public Die {
 private:
  bool isPath;
 public:
  Lava(Level* l, float x, float y);
  
  bool hitBob(Bob* b);

  void setPath() {isPath=true;}

  void act();
  void render(sf::RenderWindow& window);
};

#endif
