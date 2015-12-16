#include "Web.h"
#include <utilities.h>
#include <Level.h>

Web::Web(Level* l, float x_, float y_) : 
  Switch(l,x_,y_,32,32) {
  static_cast<sf::CircleShape*>(shape)->setFillColor(sf::Color(200,200,200));
}

int Web::activate() {
  Switch::activate();
  level->getBob()->web();
  return 0;
}


void Web::render(sf::RenderWindow& window) {
  static_cast<sf::CircleShape*>(shape)->setPosition(getX1(),getY1());
  window.draw(*shape);
}
