#include "Crystal.h"
#include <utilities.h>
#include <Level.h>
#include <GemDoor.h>
#include <stdio.h>
Crystal::Crystal(Level* l, float x_, float y_, C_CODE col,std::vector<GemDoor*>* ds) : 
  Collectable(l,x_,y_,l->getWidth(),l->getHeight()) {
  c=col;
  doors = ds;
  for (unsigned int i=0;i<doors->size();i++)
    (*doors)[i]->addCrystal();

 std::vector<std::string> keys;
  char key[20];
  for (int i=0;i<32;i++) {
    sprintf(key,"%s_gem_%d",getColorString(c),i);
    keys.push_back(std::string(key));
  }
  texture_keys.push_back(keys);
}

std::vector<Line> Crystal::getLines() const {
  std::vector<Line> lines;
  if (c!=COIN) {
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
  }
  return lines;
}

std::vector<Circle> Crystal::getCircles() const {
  std::vector<Circle> circles;
  if (c==COIN)
    circles.push_back(Circle(getX1()+width/2,getY1()+height/2,width/5+3));
  return circles;
}

int Crystal::activate() {
  Collectable::activate();
  for (unsigned int i=0;i<doors->size();i++)
    (*doors)[i]->removeCrystal();
  return getColorScore(c);
}

void Crystal::render(sf::RenderWindow& window) {
  Actor::render(window);
  texture_step++;
}
