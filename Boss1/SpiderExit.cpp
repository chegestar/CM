#include "SpiderBoss.h"
#include <Level.h>
SpiderExit::SpiderExit(Level*l, ShooterSpider* b, float x_) :
  Switch(l,x_,13*32,32,32){
  boss = b;
}


int SpiderExit::activate() {
  
  boss->start();
  setDead();
  return 0;
}
