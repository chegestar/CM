#include "Coin.h"
#include <utilities.h>
#include <Level.h>

Coin::Coin(Level* l, float x_, float y_) : 
  Collectable(l,x_,y_,15,15) {
  static_cast<sf::CircleShape*>(shape)->setFillColor(sf::Color(200,200,0));
}

int Coin::activate() {
  Collectable::activate();
  return 10;
}


void Coin::render(sf::RenderWindow& window) {
  static_cast<sf::CircleShape*>(shape)->setPosition(getX1(),getY1());
  window.draw(*shape);
}
