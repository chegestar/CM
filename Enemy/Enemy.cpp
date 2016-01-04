#include "Enemy.h"
#include <Bob.h>
#include <utilities.h>
#include <Level.h>

Enemy::Enemy(Level* l, float x, float y, float w, float h) : 
  Actor(l,x,y,w,h), Die(l,x,y,w,h), Mover(l,x,y,w,h) {
}

void Enemy::act() {
  Mover::act();
  Die::act();
}
