#include "Fire.h"
#include <Level.h>

Fire::Fire(Level* l, float x, float y) : 
  Actor(l,x,y,l->getWidth(),l->getHeight()), Die(l,x,y,width,height) {
  static_cast<sf::CircleShape*>(shape)->setFillColor(sf::Color(255,0,0));


}


void Fire::render(sf::RenderWindow& window) {

  static_cast<sf::CircleShape*>(shape)->setPosition(getX1(),getY1());
  window.draw(*shape);

}
