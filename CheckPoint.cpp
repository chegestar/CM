#include "CheckPoint.h"

void CheckPoint::render(sf::RenderWindow& window) {
  sf::CircleShape shape(width/2);
  shape.setPosition(x,y);
  shape.setFillColor(sf::Color(0,255,0));
  window.draw(shape);

}

