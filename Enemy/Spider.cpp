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
  delete [] bs;
  Enemy::act();
}

