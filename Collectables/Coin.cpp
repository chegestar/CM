#include "Coin.h"
#include <utilities.h>
#include <Level.h>

Coin::Coin(Level* l, float x_, float y_) : 
  Collectable(l,x_,y_,l->getWidth(),l->getHeight()) {
  std::vector<std::string> keys;
  for (int i=0;i<32;i++) {
    char key[40];
    sprintf(key,"coin_gem_%d",i);
    keys.push_back(key);
  }
  texture_keys.push_back(keys);

}

std::vector<Circle> Coin::getCircles() const {
  std::vector<Circle> circles;
  circles.push_back(Circle(getX1()+width/2,getY1()+height/2,width/5+3));
  return circles;
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
