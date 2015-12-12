#include "Exit.h"
#include <Level.h>

Exit::Exit(Level* l, float x_,float y_) : 
  CheckPoint(l,x_,y_) {};

void Exit::render(sf::RenderWindow& window) {
  sf::CircleShape shape(width/2);
  shape.setPosition(getX1(),getY1());
  shape.setFillColor(sf::Color(170,170,30));
  window.draw(shape);

}

