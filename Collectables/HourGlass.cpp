#include "HourGlass.h"
#include <Level.h>

HourGlass::HourGlass(Level* l, float x_, float y_,bool isR) : 
  Collectable(l,x_,y_,l->getWidth(),l->getHeight()) {
  isRed=isR;
  std::vector<std::string> keys;
  for (int i=0;i<12;i++) {
    char key[20];
    if (isRed)
      sprintf(key,"hourglass_red_%d",i);
    else
      sprintf(key,"hourglass_black_%d",i);
    keys.push_back(key);
  }
  texture_keys.push_back(keys);

}

std::vector<Line> HourGlass::getLines() const {
  std::vector<Line> lines;
  float x1 = getX1()+2;
  float x2 = getX2()-2;
  float y1 = getY1()+2;
  float y2 = getY2()-2;
  lines.push_back(Line(x1,y1,x2,y2));
  lines.push_back(Line(x2,y1,x1,y2));
  lines.push_back(Line(x1,y1,x2,y1));
  lines.push_back(Line(x1,y2,x2,y2));
  return lines;
}

int HourGlass::activate() {
  Collectable::activate();
  level->setSpiders(isRed);
  return 5;
}


void HourGlass::render(sf::RenderWindow& window) {
  texture_step++;
  Actor::render(window);
}
