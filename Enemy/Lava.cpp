#include "Lava.h"
#include <Level.h>
#include <FireBoot.h>
#include <Codes.h>
#include <Rock.h>
#include <utilities.h>

Lava::Lava(Level* l, float x, float y) : 
  Actor(l,x,y,l->getWidth(),l->getHeight()), Die(l,x,y,width,height) {
  isPath=false;
  char key[20];
  std::vector<std::string> keys;
  for (int i=0;i<5;i++) {
    sprintf(key,"fire_%d",i);
    keys.push_back(key);
  }
  texture_keys.push_back(keys);
  light=NULL;
  if (l->getZone()==ICE) {

    float rad = l->getWidth()*3.5/2;
    light = new Light(level,x,y,rad);
  }
}
Lava::~Lava() {
  if (light)
    delete light;
}

bool Lava::hitBob(Bob* b) {
  if (!b->hasItem(FIRE_BOOT)) {
    return Die::hitBob(b);
  }
  return false;
}

void Lava::act() {
  texture_step++;
  if (isPath) {
    Bob* b = level->getBob();
    if (hitBob(b)) {
      b->drain();
    }
  } 
  else {
    Die::act();
    std::list<Rock*> rocks = level->getRocks();
    std::list<Rock*>::iterator itr;
    for (itr=rocks.begin();itr!=rocks.end();itr++)
      if (isRectangularHit(this,*itr))
        (*itr)->setDead();
  }
  if (light&&isRectangularHit(level->getBob(),light)) {
    light->activate();
  }
}

void Lava::render(sf::RenderWindow& window) {
  if (level->getZone()==ICE) {
    light->render(window);
  }
  Actor::render(window);

}
