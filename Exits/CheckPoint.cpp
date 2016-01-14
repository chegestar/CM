#include "CheckPoint.h"
#include <Level.h>
#include <Bob.h>
#include <utilities.h>
CheckPoint::CheckPoint(Level* l, float x_,float y_) : 
  Actor(l,x_,y_,l->getWidth()-3,l->getHeight()-3) {
  
  texture_keys.push_back(std::vector<std::string>(1,"checkpoint"));
  texture_keys.push_back(std::vector<std::string>(1,"checkpoint_hit"));
};

std::vector<Circle> CheckPoint::getCircles() const {
  return std::vector<Circle>(1,Circle(getX1()+width/2,getY1()+height/2,width/2-2));
}

void CheckPoint::act() {
  if (isRectangularHit(this,level->getBob())) {

    activate();
  }
  float sx,sy;
  level->getBob()->getStart(sx,sy);
  texture_set=0;
  
  if (sx==x&&sy==y)
    texture_set=1;

}
