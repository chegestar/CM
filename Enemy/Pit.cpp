#include "Pit.h"
#include <Level.h>

Pit::Pit(Level* l, float x, float y) : 
  Actor(l,x,y,l->getWidth(),l->getHeight()), Die(l,x,y,width,height) {
  static_cast<sf::CircleShape*>(shape)->setFillColor(sf::Color(0,0,0));
}


void Pit::render(sf::RenderWindow& window) {

  static_cast<sf::CircleShape*>(shape)->setPosition(getX1(),getY1());
  window.draw(*shape);

}
