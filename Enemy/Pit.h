#include <Die.h>

#ifndef __PIT__H__
#define __PIT__H__

class Pit : public Die {
 public:
  Pit(Level* l, float x, float y);

  void render(sf::RenderWindow& window);
};

#endif
