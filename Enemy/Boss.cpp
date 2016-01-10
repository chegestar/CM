#include "Boss.h"
#include <Bob.h>
#include <Level.h>
Boss::Boss(Level* l, float x_, float y_, float w, float h) :
  Actor(l,x_,y_,w,h), Enemy(l,x_,y_,w,h) {
  hp=0;
  shape = new sf::CircleShape(width/2);
  bob_lives=l->getBob()->getLives();
}

void Boss::act() {
  if (level->getBob()->getLives()<bob_lives)
    reset();
  bob_lives = level->getBob()->getOldLives();
  if (hp==0)
    setDead();
  Enemy::act();
}

