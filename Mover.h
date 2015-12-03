
#include "Actor.h"

#ifndef __MOVER__H__
#define __MOVER__H__

class Mover : virtual public Actor {
 public:
  Mover(Level* l, float x_,float y_,float w,float h);
  
  float getLastX1() const {return lastx;}
  float getLastX2() const {return lastx+width;}
  float getLastY1() const {return lasty;}
  float getLastY2() const {return lasty+height;}
  bool isStationary() const {return false;}
  void act();
  float getMovementCorrectionX(float speed);
  float getMovementCorrectionY(float speed);
 protected:
  float lastx,lasty;
};

#endif
