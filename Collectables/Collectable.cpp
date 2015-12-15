#include "Collectable.h"
#include <utilities.h>
#include <Level.h>
#include <GemDoor.h>

Collectable::Collectable(Level* l, float x_, float y_, float w, float h) : 
  Actor(l,x_,y_,w,h) {
  shape = new sf::CircleShape(width/2);
  static_cast<sf::CircleShape*>(shape)->setFillColor(sf::Color(0,0,255));
}

int Collectable::activate() {
  isDead=true;
  return 0;
}


void Collectable::render(sf::RenderWindow& window) {
  static_cast<sf::CircleShape*>(shape)->setPosition(getX1(),getY1());
  window.draw(*shape);
}
