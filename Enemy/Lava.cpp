#include "Lava.h"
#include <Level.h>
#include <FireBoot.h>
#include <Codes.h>
#include <Rock.h>
#include <utilities.h>

Lava::Lava(Level* l, float x, float y) : 
  Actor(l,x,y,l->getWidth(),l->getHeight()), Die(l,x,y,width,height) {
  isPath=false;
  
  static_cast<sf::CircleShape*>(shape)->setFillColor(sf::Color(255,0,0));
}

bool Lava::hitBob(Bob* b) {
  bool isHit = false;
  if (!b->hasItem(FIRE_BOOT)) {
    isHit = Die::hitBob(b);
  }
  return isHit;
}

void Lava::act() {

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

  static_cast<sf::CircleShape*>(shape)->setPosition(getX1(),getY1());
  window.draw(*shape);

}
