#include "Block.h"
#include <Level.h>

Block::Block(Level* l,float x_,float y_) : 
  Actor(l,x_,y_,l->getWidth(),l->getHeight()) {

  shape = new sf::RectangleShape(sf::Vector2f(width,height));
  static_cast<sf::RectangleShape*>(shape)->setFillColor(sf::Color(50,50,50));
  isL=isR=isU=isD=true;
}

void Block::push_back(Actor* actor, int dir) {
  if (isD&&dir%2)
    actor->setPosition(actor->getX1(),getY2());
  if (isL&&((dir>>1)%2))
    actor->setPosition(getX1()-actor->getWidth(),actor->getY1());
  if (isU&&((dir>>2)%2))
    actor->setPosition(actor->getX1(),getY1()-actor->getHeight());
  if (isR&&((dir>>3)%2))
    actor->setPosition(getX2(),actor->getY1());
  
}

void Block::render(sf::RenderWindow& window) {
  static_cast<sf::RectangleShape*>(shape)->setPosition(getX1(),getY1());
  window.draw(*shape);
}
