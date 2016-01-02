#include "Ghost.h"
#include <Bob.h>
#include <utilities.h>
#include <Level.h>
#include <Block.h>


Ghost::Ghost(Level* l, float x, float y) : 
  Actor(l,x,y,32*4.0/5,32*4.0/5), Enemy(l,x,y,width,height) {
  angle = getRand(0,M_PI*2);
};


void Ghost::act() {
  Mover::act();
  const int speed = 2;
  
  x+=speed*cos(angle);
  y+=speed*sin(angle);

  float rand = getRand(0,1);
  if (rand<.55/60) 
    angle = getRand(0,M_PI*2);

  std::vector<Actor*> hits;
  level->testHitStationary(this,hits);
  for (unsigned int i=0;i<hits.size();i++) {
    if (dynamic_cast<Block*>(hits[i])) {
      int dir = getApproachDir(this,hits[i]);
      if (dir==0&&getLastX1()!=hits[i]->getX2()&&getLastX2()!=hits[i]->getX1()) {
        setPosition(getX1(),hits[i]->getY2());
      }
      else if (dir==1)
        setPosition(hits[i]->getX1()-width,getY1());
      else if (dir==2&&getLastX1()!=hits[i]->getX2()&&getLastX2()!=hits[i]->getX1())
        setPosition(getX1(),hits[i]->getY1()-height);
      else if (dir==3)
        setPosition(hits[i]->getX2(),getY1());
      angle = getRand(0,M_PI*2);
    }
  }
  Enemy::act();
}

