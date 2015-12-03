#include "CheckPoint.h"
#include <Level.h>

CheckPoint::CheckPoint(Level* l, float x_,float y_) : 
  Actor(l,x_,y_,l->getWidth(),l->getHeight()) {};

void CheckPoint::render(sf::RenderWindow& window) {
  sf::CircleShape shape(width/2);
  shape.setPosition(x,y);
  shape.setFillColor(sf::Color(0,255,0));
  window.draw(shape);

}

