#include "Web.h"
#include <utilities.h>
#include <Level.h>

Web::Web(Level* l, float x_, float y_) : 
  Switch(l,x_,y_,32,32) {
  texture_keys.push_back(std::vector<std::string>(1,"web"));
}

std::vector<Line> Web::getLines() const {
  std::vector<Line> lines;
  lines.push_back(Line(getBoundX1(),getBoundY1(),getBoundX2(),getBoundY1()));
  lines.push_back(Line(getBoundX1(),getBoundY1(),getBoundX1(),getBoundY2()));
  lines.push_back(Line(getBoundX2(),getBoundY1(),getBoundX2(),getBoundY2()));
  lines.push_back(Line(getBoundX1(),getBoundY2(),getBoundX2(),getBoundY2()));
  return lines;
}

std::vector<Circle> Web::getCircles() const {
  std::vector<Circle> circles;
  circles.push_back(Circle(getX1()+width/2,getY1()+height/2,height/4));
  return circles;
}

int Web::activate() {
  Switch::activate();
  level->getBob()->web();
  return 0;
}


