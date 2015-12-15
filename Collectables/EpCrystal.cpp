#include "EpCrystal.h"
#include <utilities.h>
#include <Level.h>
#include <Bob.h>

EpCrystal::EpCrystal(Level* l, float x_, float y_) : 
  Collectable(l,x_,y_,15,15) {
  static_cast<sf::CircleShape*>(shape)->setFillColor(sf::Color(200,0,200));
}

int EpCrystal::activate() {
  Collectable::activate();
  level->getBob()->earnEP();
  return 1000;
}


void EpCrystal::render(sf::RenderWindow& window) {
  static_cast<sf::CircleShape*>(shape)->setPosition(getX1(),getY1());
  window.draw(*shape);
}
