#include "Coin.h"
#include <utilities.h>
#include <Level.h>

Coin::Coin(Level* l, float x_, float y_) : 
  Collectable(l,x_,y_,l->getWidth(),l->getHeight()) {
  texture_keys.push_back("coin_gem");

}

int Coin::activate() {
  Collectable::activate();
  level->getBob()->earnCoin();
  return 10;
}


void Coin::render(sf::RenderWindow& window) {
  texture_step++;
  Actor::render(window);
}
