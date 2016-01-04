#ifndef __CHECKPOINT__H__
#define __CHECKPOINT__H__

#include <Actor.h>
#include <Level.h>

class CheckPoint : public Actor {
 public:
  CheckPoint(Level* l, float x_,float y_);
  
  int activate() {level->getBob()->setCheckPoint(x,y);return 0;}

  void act();

 
};

#endif
