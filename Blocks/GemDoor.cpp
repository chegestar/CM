#include "GemDoor.h"
#include <Level.h>
GemDoor::GemDoor(Level* l,int x,int y) : Actor(l,x,y,l->getWidth(),l->getHeight()), Block(l,x,y) {
  num_gems=0;
  static_cast<sf::RectangleShape*>(shape)->setFillColor(sf::Color(0,0,255));
}

void GemDoor::act() {

}

void GemDoor::render(sf::RenderWindow& window) {

  static_cast<sf::RectangleShape*>(shape)->setPosition(getX1(),getY1());

  window.draw(*shape);
}
