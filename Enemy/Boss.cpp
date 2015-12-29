#include "Boss.h"

Boss::Boss(Level* l, float x_, float y_, float w, float h) :
  Actor(l,x_,y_,w,h), Enemy(l,x_,y_,w,h) {
  hp=0;
}

void Boss::act() {
  if (hp==0)
    setDead();
  Enemy::act();
}
