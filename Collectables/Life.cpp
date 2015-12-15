#include "Life.h"
#include <utilities.h>
#include <Level.h>
#include <Bob.h>

Life::Life(Level* l, float x_, float y_) : 
  Collectable(l,x_,y_,20,20) {
  static_cast<sf::CircleShape*>(shape)->setFillColor(sf::Color(255,105,180));
}

int Life::activate() {
  Collectable::activate();
  level->getBob()->earnLife();
  return 10;
}


void Life::render(sf::RenderWindow& window) {
  static_cast<sf::CircleShape*>(shape)->setPosition(getX1(),getY1());
  window.draw(*shape);
}
