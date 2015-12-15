#include "Exit.h"
#include <Level.h>

Exit::Exit(Level* l, float x_,float y_) : 
  CheckPoint(l,x_,y_) {
  static_cast<sf::CircleShape*>(shape)->setFillColor(sf::Color(170,170,30));
};

void Exit::render(sf::RenderWindow& window) {
  static_cast<sf::CircleShape*>(shape)->setPosition(getX1(),getY1());
  window.draw(*shape);

}

