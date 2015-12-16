#include "Switch.h"
#include <utilities.h>
#include <Level.h>

Switch::Switch(Level* l, float x_, float y_, float w, float h) : 
  Actor(l,x_,y_,w,h) {
  shape = new sf::CircleShape(width/2);
  static_cast<sf::CircleShape*>(shape)->setFillColor(sf::Color(0,0,255));

}

void Switch::render(sf::RenderWindow& window) {
  static_cast<sf::CircleShape*>(shape)->setPosition(getX1(),getY1());
  window.draw(*shape);
}
