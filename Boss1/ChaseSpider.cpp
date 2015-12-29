#include "SpiderBoss.h"
#include <Lava.h>
#include <Level.h>

ChaseSpider::ChaseSpider(Level* l, int index) :
  Actor(l,-100,33+index*96,100,32*3-2),Boss(l,x,y,width,height) {
  hp=1;
  isMove=false;
}

void ChaseSpider::act() {
  if (level->getBob()->getX2()>level->getWindowWidth()-level->getWidth()*2)
    isMove=true;
  if (isMove) {
    x+=1.8;
    if (x>-width*1/4)
      level->unhalt();
    std::vector<Actor*> stationary;
    level->testHitStationary(this,stationary);
    for (unsigned int i=0;i<stationary.size();i++) 
      if (dynamic_cast<Lava*>(stationary[i]))
        hp=0;
  }

  Boss::act();
}
