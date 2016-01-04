#include "MagicRing.h"
#include <Level.h>

MagicRing::MagicRing(Level* l, float x_, float y_) : 
  Collectable(l,x_,y_,l->getWidth(),l->getHeight()) {
  texture_keys.push_back("magic_ring");

}

int MagicRing::activate() {
  Collectable::activate();
  level->getBob()->earnMagicRing();
  return 0;
}


void MagicRing::render(sf::RenderWindow& window) {
  texture_step++;
  Actor::render(window);
}
