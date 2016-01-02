#include <Enemy.h>

#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

class Explosion : public Enemy {
 public:
  Explosion(Level* l, float x_, float y_);
  
  void act();
  void render(sf::RenderWindow& window);
};
#endif
