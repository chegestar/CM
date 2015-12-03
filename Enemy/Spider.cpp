#include "Spider.h"
#include <Bob.h>
#include <utilities.h>
#include <Level.h>
#include <Block.h>


Spider::Spider(Level* l, float x, float y, float w, float h,bool d) : 
  Actor(l,x,y,w,h), Enemy(l,x,y,w,h) {

  isVert=d;
  dir=getRandInt(0,1)*2-1;
};

void Spider::act() {
  Mover::act();
  const int speed = 3;
  if (isVert)
    y+=dir*getMovementCorrectionY(speed);
  else
    x+=dir*getMovementCorrectionX(speed);

  Actor** bs;
  bs = level->testHitStationary(this);
  for (int i=0;i<4;i++) {
    if (!bs[i]) continue;
    if (dynamic_cast<Block*>(bs[i]))
      dir*=-1;
  }

  Enemy::act();
}

