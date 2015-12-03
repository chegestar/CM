#include "Enemy.h"
#include <Bob.h>
#include <utilities.h>
#include <Level.h>

bool Enemy::hitBob(Bob* b) {
  return isRectangularHit(b,this);
    
}

void Enemy::act() {
  if (hitBob(level->getBob())) {
    level->getBob()->die();
  }
}

void Enemy::render(sf::RenderWindow& window) {
  sf::CircleShape shape(width/2);
  shape.setPosition(getX1(),getY1());
  shape.setFillColor(sf::Color(255,0,0));
  window.draw(shape);

}
