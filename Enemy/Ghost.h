#include <Enemy.h>

#ifndef __GHOST__H__
#define __GHOST__H__

class Ghost : public Enemy {
 private:
  float angle;
 public:
  Ghost(Level* l, float x, float y);
  
  virtual void act();
};

#endif
