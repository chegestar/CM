#include "Bullet.h"
#include <Level.h>

Bullet::Bullet(Level* l, float x, float y, float w, float h,float ang, float vel) : 
  Actor(l,x,y,w,h), Enemy(l,x,y,w,h) {
  angle = ang;
  v = vel;
  static_cast<sf::CircleShape*>(shape)->setFillColor(sf::Color(0,0,0));
}

void Bullet::act() {
  Enemy::act();
  x+=cos(angle)*v;
  y+=sin(angle)*v;
  if (level->isOutOfBounds(this))
    setDead();
}
