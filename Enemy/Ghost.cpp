#include "Ghost.h"
#include <Bob.h>
#include <utilities.h>
#include <Level.h>
#include <Block.h>


Ghost::Ghost(Level* l, float x, float y) : 
  Actor(l,x,y,32,32), Enemy(l,x,y,width,height) {
  angle = getRand(0,M_PI*2);

  texture_keys.push_back("ghost");
  texture_keys.push_back("weak_ghost");
};


void Ghost::act() {
  Mover::act();
  const int speed = 2;
  
  x+=speed*cos(angle);
  y+=speed*sin(angle);

  texture_step++;
  if (level->getBob()->isInvuln())
    texture_set=1;
  else
    texture_set=0;
  float rand = getRand(0,1);
  if (rand<.55/60) 
    angle = getRand(0,M_PI*2);

  std::vector<Actor*> hits;
  level->testHitStationary(this,hits);
  for (unsigned int i=0;i<hits.size();i++) {
    if (dynamic_cast<Block*>(hits[i])) {
      int dir = getApproachDir(this,hits[i]);
      Block* b = dynamic_cast<Block*>(hits[i]);
      b->push_back(this,dir);

      angle = getRand(0,M_PI*2);
    }
  }
  Enemy::act();
}

