#include "Boss.h"

Boss::Boss(Level* l, float x_, float y_, float w, float h) :
  Actor(l,x_,y_,w,h), Enemy(l,x_,y_,w,h) {
  hp=0;
  shape = new sf::CircleShape(width/2);
}

void Boss::act() {
  if (hp==0)
    setDead();
  Enemy::act();
}


// void Boss::render(sf::RenderWindow& window) {
//   static_cast<sf::CircleShape*>(shape)->setPosition(getX1(),getY1());
//   window.draw(*shape);
// }
