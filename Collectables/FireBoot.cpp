#include "FireBoot.h"
#include <Level.h>

FireBoot::FireBoot(Level*l, float x_,float y_) :
  Item(l,x_,y_,l->getWidth(),l->getHeight()) {
  texture_keys.push_back("fireboot");
}

void FireBoot::render(sf::RenderWindow& window) {
  texture_step++;
  Actor::render(window);
}
