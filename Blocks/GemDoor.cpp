#include "GemDoor.h"

void GemDoor::act() {

}

void GemDoor::render(sf::RenderWindow& window) {
  sf::RectangleShape shape(sf::Vector2f(width,height));
  shape.setPosition(getX1(),getY1());
  shape.setFillColor(sf::Color(0,0,255));
  window.draw(shape);
}
