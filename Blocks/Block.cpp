#include "Block.h"

void Block::act() {

}

void Block::render(sf::RenderWindow& window) {
  sf::RectangleShape shape(sf::Vector2f(width,height));
  shape.setPosition(x,y);
  shape.setFillColor(sf::Color(0,0,0));
  window.draw(shape);
}
