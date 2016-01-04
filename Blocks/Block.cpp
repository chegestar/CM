#include "Block.h"
#include <Level.h>
#include <Codes.h>

Block::Block(Level* l,float x_,float y_) : 
  Actor(l,x_,y_,l->getWidth(),l->getHeight()) {
  isL=isR=isU=isD=true;

  if (l->getZone()==CAVE) {
    texture_keys.push_back("cave_mid");
    texture_keys.push_back("cave_horiz");
    texture_keys.push_back("cave_vert");
  }
  else if (l->getZone()==CRYSTAL) {
    texture_keys.push_back("crystal_mid");
    texture_keys.push_back("crystal_horiz");
    texture_keys.push_back("crystal_vert");

  }
  else if (l->getZone()==LAVA) {
    texture_keys.push_back("lava_mid");
    texture_keys.push_back("lava_horiz");
    texture_keys.push_back("lava_vert");

  }
  else if (l->getZone()==PYRAMID) {
    texture_keys.push_back("pyramid_mid");
    texture_keys.push_back("pyramid_horiz");
    texture_keys.push_back("pyramid_vert");
  }
  else if (l->getZone()==ICE) {
  }
  else if (l->getZone()==DARK) {
  }
  else if (l->getZone()==FACTORY) {
  }
  else if (l->getZone()==SPECIAL) {
  }
  else if (l->getZone()==HUB) {
  }


}

void Block::push_back(Actor* actor, int dir) {
  if (isD&&dir%2)
    actor->setPosition(actor->getX1(),getY2());
  if (isL&&((dir>>1)%2))
    actor->setPosition(getX1()-actor->getWidth(),actor->getY1());
  if (isU&&((dir>>2)%2))
    actor->setPosition(actor->getX1(),getY1()-actor->getHeight());
  if (isR&&((dir>>3)%2))
    actor->setPosition(getX2(),actor->getY1());
  
}

void Block::setDirs(bool u,bool r, bool d, bool l) {
  isL=!l;
  isR=!r;
  isU=!u;
  isD=!d;
  texture_set=0;
  if (isL+isR+isU+isD==2) {
    if (isL&&isR)
      texture_set=2;
    if (isU&&isD)
      texture_set=1;
  }
}

void Block::render(sf::RenderWindow& window) {
  Actor::render(window);
  texture_step++;
}
