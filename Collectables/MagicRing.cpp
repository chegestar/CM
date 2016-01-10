#include "MagicRing.h"
#include <Level.h>

MagicRing::MagicRing(Level* l, float x_, float y_) : 
  Collectable(l,x_,y_,l->getWidth(),l->getHeight()) {
  std::vector<std::string> keys;
  for (int i=0;i<32;i++) {
    char key[20];
    sprintf(key,"magic_ring_%d",i);
    
  }
  texture_keys.push_back(keys);

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
