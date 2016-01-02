#include "Spider.h"
#include <Bob.h>
#include <utilities.h>
#include <Level.h>
#include <Block.h>


Spider::Spider(Level* l, float x, float y,bool d) : 
  Actor(l,x,y,32*4.0/5,32*4.0/5), Enemy(l,x,y,width,height) {

  isVert=d;
  dir=getRandInt(0,1)*2-1;
};

void Spider::act() {
  Mover::act();
  const int speed = 2;
  if (isVert)
    y+=dir*getMovementCorrectionY(speed);
  else
    x+=dir*getMovementCorrectionX(speed);

  std::vector<Actor*> hits;
  level->testHitStationary(this,hits);
  for (unsigned int i=0;i<hits.size();i++) {
    if (dynamic_cast<Block*>(hits[i])) {
      int d = getApproachDir(this,hits[i]);
      if (d%2 || (d>>3)%2)
        dir = 1;
      else if ((d>>1)%2 || (d>>2)%2)
        dir=-1;
    }
  }
  Enemy::act();
}

