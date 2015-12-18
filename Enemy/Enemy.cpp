#include "Enemy.h"
#include <Bob.h>
#include <utilities.h>
#include <Level.h>

Enemy::Enemy(Level* l, float x, float y, float w, float h) : 
  Actor(l,x,y,w,h), Die(l,x,y,w,h), Mover(l,x,y,w,h) {
  static_cast<sf::CircleShape*>(shape)->setFillColor(sf::Color(255,0,0));


}

void Enemy::act() {
  Mover::act();
  Die::act();
}

void Enemy::render(sf::RenderWindow& window) {

  static_cast<sf::CircleShape*>(shape)->setPosition(getX1(),getY1());
  window.draw(*shape);

}
