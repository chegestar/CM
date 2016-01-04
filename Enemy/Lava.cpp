#include "Lava.h"
#include <Level.h>
#include <FireBoot.h>
#include <Codes.h>
#include <Rock.h>
#include <utilities.h>

Lava::Lava(Level* l, float x, float y) : 
  Actor(l,x,y,l->getWidth(),l->getHeight()), Die(l,x,y,width,height) {
  isPath=false;
  texture_keys.push_back("fire");
}

bool Lava::hitBob(Bob* b) {
  bool isHit = false;
  if (!b->hasItem(FIRE_BOOT)) {
    isHit = Die::hitBob(b);
  }
  return isHit;
}

void Lava::act() {
  texture_step++;
  if (isPath) {
    Bob* b = level->getBob();
    if (hitBob(b)) {
      b->drain();
    }
  } else { //Just for you Justin
    Die::act();
    std::list<Rock*> rocks = level->getRocks();
    std::list<Rock*>::iterator itr;
    for (itr=rocks.begin();itr!=rocks.end();itr++)
      if (isRectangularHit(this,*itr))
        (*itr)->setDead();
  }
}

void Lava::render(sf::RenderWindow& window) {
  Actor::render(window);

}
