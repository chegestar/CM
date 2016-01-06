#include "CheckPoint.h"
#include <Level.h>
#include <Bob.h>
#include <utilities.h>
CheckPoint::CheckPoint(Level* l, float x_,float y_) : 
  Actor(l,x_,y_,l->getWidth()-3,l->getHeight()-3) {
  
  texture_keys.push_back("checkpoint");
  texture_keys.push_back("checkpoint_hit");
};

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
