#include "Block.h"
#include <Level.h>

Block::Block(Level* l,float x_,float y_) : 
  Actor(l,x_,y_,l->getWidth(),l->getHeight()) {

  shape = new sf::RectangleShape(sf::Vector2f(width,height));
  static_cast<sf::RectangleShape*>(shape)->setFillColor(sf::Color(50,50,50));

}

void Block::act() {

}

void Block::render(sf::RenderWindow& window) {
  static_cast<sf::RectangleShape*>(shape)->setPosition(getX1(),getY1());
  window.draw(*shape);
}
