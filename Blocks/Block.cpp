#include "Block.h"
#include <Level.h>

Block::Block(Level* l,float x_,float y_) : 
  Actor(l,x_,y_,l->getWidth(),l->getHeight()) {}

void Block::act() {

}

void Block::render(sf::RenderWindow& window) {
  sf::RectangleShape shape(sf::Vector2f(width,height));
  shape.setPosition(getX1(),getY1());
  shape.setFillColor(sf::Color(0,0,0));
  window.draw(shape);
}
