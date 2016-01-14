#include "EpCrystal.h"
#include <utilities.h>
#include <Level.h>
#include <Bob.h>

EpCrystal::EpCrystal(Level* l, float x_, float y_) : 
  Collectable(l,x_,y_,l->getWidth(),l->getHeight()) {
  std::vector<std::string> keys;
  int i=0;
  for (C_CODE col=RED;i<32;getNextColor(col)) {
    if (col==COIN)
      col=RED;
    char key[15];
    sprintf(key,"%s_gem_%d",getColorString(col),i);
    keys.push_back(key);
    i++;
  }
  texture_keys.clear();
  texture_keys.push_back(keys);
}

std::vector<Line> EpCrystal::getLines() const {
  std::vector<Line> lines;
  float rightX = getX1()+width/4*3+1.5;
  float leftX = getX1()+width/4-1.5;
  float topY = getY1()+height/3-1;
  float bottomY = getY1()+height/3*2+1;
  lines.push_back(Line(getX1()+width/2,getY1()+2,rightX,topY));
  lines.push_back(Line(getX1()+width/2,getY1()+2,leftX,topY));
  lines.push_back(Line(rightX,topY,rightX,bottomY));
  lines.push_back(Line(leftX,topY,leftX,bottomY));
  lines.push_back(Line(getX1()+width/2,getY2()-2,rightX,bottomY));
  lines.push_back(Line(getX1()+width/2,getY2()-2,leftX,bottomY));

  return lines;
}


int EpCrystal::activate() {
  Collectable::activate();
  level->getBob()->earnEP();
  return 1000;
}


void EpCrystal::render(sf::RenderWindow& window) {
  Actor::render(window);
  texture_step++;
}
