#include "Spider.h"
#include <Bob.h>
#include <utilities.h>
#include <Level.h>
#include <Rock.h>


Spider::Spider(Level* l, float x, float y,bool d, int di) :
  Actor(l,x,y,32*4.0/5,32*4.0/5), Enemy(l,x,y,width,height) {

  isVert=d;
  dir=di;
  if (dir==0)
    dir=getRandInt(0,1)*2-1;
  char key[20];
  std::vector<std::string> keys;
  for (int i=0;i<8;i++) {
    sprintf(key,"Hspider_%d",i);
    keys.push_back(key);
  }
  texture_keys.push_back(keys);
  keys.clear();
  for (int i=0;i<8;i++) {
    sprintf(key,"Vspider_%d",i);
    keys.push_back(key);
  }
  texture_keys.push_back(keys);
  texture_set=isVert;
};

std::vector<Line> Spider::getLines() const {
  std::vector<Line> lines;
  lines.push_back(Line(getX1(),getBoundY1(),getX2(),getBoundY1()));
  lines.push_back(Line(getX1(),getBoundY1(),getX1(),getBoundY2()));
  lines.push_back(Line(getX2(),getBoundY1(),getX2(),getBoundY2()));
  lines.push_back(Line(getX1(),getBoundY2(),getX2(),getBoundY2()));
  return lines;
}

void Spider::act() {
  Mover::act();
  const int speed = getSpeed();
  if (isVert)
    y+=dir*getMovementCorrectionY(speed);
  else
    x+=dir*getMovementCorrectionX(speed);
  texture_step++;
  std::vector<Actor*> hits;
  level->testHitStationary(this,hits);
  for (unsigned int i=0;i<hits.size();i++) {
    int d = getApproachDir(this,hits[i]);
    if (dynamic_cast<Block*>(hits[i])) {

      if (d%2 || (d>>3)%2) 
        dir = 1;
        
      else if ((d>>1)%2 || (d>>2)%2)
        dir=-1;
      dynamic_cast<Block*>(hits[i])->push_back(this,d);
      
    }
  }
  hits.clear();
  level->testHitStationary(this,hits);
  for (unsigned int i=0;i<hits.size();i++) {
    if (dynamic_cast<Block*>(hits[i])) {
      setDead();
    }
  }
  
  Enemy::act();
}


void Spider::render(sf::RenderWindow& window) {
  Actor::render(window);
}
