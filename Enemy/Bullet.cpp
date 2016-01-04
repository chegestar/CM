#include "Bullet.h"
#include <Level.h>

Bullet::Bullet(Level* l, float x, float y, float w, float h,float ang, float vel) : 
  Actor(l,x,y,w,h), Enemy(l,x,y,w,h) {
  angle = ang;
  v = vel;
}

void Bullet::act() {
  texture_step++;
  Enemy::act();
  x+=cos(angle)*v;
  y+=sin(angle)*v;
  if (level->isOutOfBounds(this))
    setDead();
}
