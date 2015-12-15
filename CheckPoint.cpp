#include "CheckPoint.h"
#include <Level.h>

CheckPoint::CheckPoint(Level* l, float x_,float y_) : 
  Actor(l,x_,y_,l->getWidth(),l->getHeight()) {
  shape = new sf::CircleShape(width/2);
  static_cast<sf::CircleShape*>(shape)->setFillColor(sf::Color(0,255,0));
};

void CheckPoint::render(sf::RenderWindow& window) {

  static_cast<sf::CircleShape*>(shape)->setPosition(getX1(),getY1());

  window.draw(*shape);

}

