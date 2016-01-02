#include "GemDoor.h"
#include <Level.h>
GemDoor::GemDoor(Level* l,int x,int y,C_CODE col) : Actor(l,x,y,l->getWidth(),l->getHeight()), Block(l,x,y) {
  num_gems=0;
  c=col;
  static_cast<sf::RectangleShape*>(shape)->setFillColor(sf::Color((c==RED)*255,0,(c==BLUE)*255));
}


void GemDoor::render(sf::RenderWindow& window) {
  static_cast<sf::RectangleShape*>(shape)->setPosition(getX1(),getY1());
  window.draw(*shape);
}
