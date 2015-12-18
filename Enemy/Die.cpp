#include "Die.h"
#include <Bob.h>
#include <utilities.h>
#include <Level.h>

Die::Die(Level* l, float x, float y, float w, float h) : 
  Actor(l,x,y,w,h) {
  shape = new sf::CircleShape(width/2);
  static_cast<sf::CircleShape*>(shape)->setFillColor(sf::Color(255,0,0));


}
bool Die::hitBob(Bob* b) {
  return isRectangularHit(b,this);
    
}

void Die::act() {
  if (hitBob(level->getBob())) {
    level->getBob()->die();
  }
}

void Die::render(sf::RenderWindow& window) {

  static_cast<sf::CircleShape*>(shape)->setPosition(getX1(),getY1());
  window.draw(*shape);

}
