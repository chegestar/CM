#include <Actor.h>

#ifndef __COLLECTABLE__H__
#define __COLLECTABLE__H__

class Collectable : public Actor {
 public:
  Collectable(Level* l, float x_, float y_, float w, float h);

  virtual int activate();

  void render(sf::RenderWindow& window);

};

#endif
