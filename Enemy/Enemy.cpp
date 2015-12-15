#include "Enemy.h"
#include <Bob.h>
#include <utilities.h>
#include <Level.h>

Enemy::Enemy(Level* l, float x, float y, float w, float h) : 
  Actor(l,x,y,w,h), Mover(l,x,y,w,h) {
  shape = new sf::CircleShape(width/2);
  static_cast<sf::CircleShape*>(shape)->setFillColor(sf::Color(255,0,0));


}
bool Enemy::hitBob(Bob* b) {
  return isRectangularHit(b,this);
    
}

void Enemy::act() {
  if (hitBob(level->getBob())) {
    level->getBob()->die();
  }
}

void Enemy::render(sf::RenderWindow& window) {

  static_cast<sf::CircleShape*>(shape)->setPosition(getX1(),getY1());
  window.draw(*shape);

}
