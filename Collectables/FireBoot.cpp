#include "FireBoot.h"
#include <Level.h>

FireBoot::FireBoot(Level*l, float x_,float y_) :
  Item(l,x_,y_,l->getWidth(),l->getHeight()) {
  std::vector<std::string> keys;
  for (int i=0;i<8;i++) {
    char key[15];
    sprintf(key,"fireboot_%d",i);
    keys.push_back(std::string(key));
  }
  texture_keys.push_back(keys);
}

void FireBoot::render(sf::RenderWindow& window) {
  texture_step++;
  Actor::render(window);
}
