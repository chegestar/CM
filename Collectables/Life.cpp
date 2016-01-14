#include "Life.h"
#include <utilities.h>
#include <Level.h>
#include <Bob.h>

Life::Life(Level* l, float x_, float y_) : 
  Collectable(l,x_,y_,l->getWidth(),l->getHeight()) {
  
  texture_keys.push_back(std::vector<std::string>(1,"life"));
}

int Life::activate() {
  Collectable::activate();
  level->getBob()->earnLife();
  return 10;
}

std::vector<Circle> Life::getCircles() const {
  return std::vector<Circle>(1,Circle(getX1()+width/2,getY1()+height/2,width/3));
}
