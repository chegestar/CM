#include "Block.h"
#include <Level.h>
#include <Codes.h>

Block::Block(Level* l,float x_,float y_) : 
  Actor(l,x_,y_,l->getWidth(),l->getHeight()) {
  isL=isR=isU=isD=true;
  Z_TYPE z= l->getZone();
  std::string zone="cave";
  int num_imgs=0;
  if (z==HUB) {
    z = l->getHubZone(x,y);
  }
  if (z==CAVE) {
    num_imgs=0;
    zone="cave";
  }
  else if (z==CRYSTAL) {
    num_imgs=13;
    zone="crystal";
  }
  else if (z==LAVA) {
    num_imgs=9;
    zone="lava";
  }
  else if (z==PYRAMID) {
    num_imgs=0;
    zone="pyramid";
  }
  else if (z==ICE) {

  }
  else if (z==DARK) {
  }
  else if (z==FACTORY) {
  }
  else if (z==SPECIAL) {
  }
  if (num_imgs>0) {
    char key[40];
    std::vector<std::string> keys;
    for (int i=0;i<num_imgs;i++) {
      sprintf(key,"%s_mid_%d",zone.c_str(),i);
      keys.push_back(key);
    }
    texture_keys.push_back(keys);
    keys.clear();
    for (int i=0;i<num_imgs;i++) {
      sprintf(key,"%s_vert_%d",zone.c_str(),i);
      keys.push_back(key);
    }
    texture_keys.push_back(keys);
    keys.clear();
    for (int i=0;i<num_imgs;i++) {
      sprintf(key,"%s_horiz_%d",zone.c_str(),i);
      keys.push_back(key);
    }
    texture_keys.push_back(keys);
    keys.clear();    
  }
  else {
    char key[40];
    std::vector<std::string> keys;
    sprintf(key,"%s_mid",zone.c_str());
    keys.push_back(key);
    texture_keys.push_back(keys);
    keys.clear();
    sprintf(key,"%s_vert",zone.c_str());
    keys.push_back(key);
    texture_keys.push_back(keys);
    keys.clear();
    sprintf(key,"%s_horiz",zone.c_str());
    keys.push_back(key);
    texture_keys.push_back(keys);
  }
}

std::vector<Line> Block::getLines() const {
  std::vector<Line> lines;
  lines.push_back(Line(getX1(),getY1(),getX2(),getY1()));
  lines.push_back(Line(getX2(),getY1(),getX2(),getY2()));
  lines.push_back(Line(getX1(),getY2(),getX2(),getY2()));
  lines.push_back(Line(getX1(),getY1(),getX1(),getY2()));
  return lines;
}


void Block::push_back(Actor* actor, int dir) {
  if (isD&&dir%2)
    actor->setPosition(actor->getX1(),getY2()+.1);
  if (isL&&((dir>>1)%2))
    actor->setPosition(getX1()-actor->getWidth()-.1,actor->getY1());
  if (isU&&((dir>>2)%2))
    actor->setPosition(actor->getX1(),getY1()-actor->getHeight()-.1);
  if (isR&&((dir>>3)%2))
    actor->setPosition(getX2()+.1,actor->getY1());
  
}

void Block::setDirs(bool u,bool ugem,bool r,bool rgem, bool d, bool dgem,bool l,bool lgem) {
  isL=!l;
  isR=!r;
  isU=!u;
  isD=!d;

  u = isU||ugem;
  d = isD||dgem;
  l = isL||lgem;
  r = isR||rgem;
  texture_set=0;
  if (l+r+u+d==2) {
    if (l&&r)
      texture_set=1;
    if (u&&d)
      texture_set=2;
  }
}

void Block::render(sf::RenderWindow& window) {
  Actor::render(window);
  texture_step++;
}
