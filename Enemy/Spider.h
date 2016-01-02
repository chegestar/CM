#include <Enemy.h>

#ifndef __SPIDER__H__
#define __SPIDER__H__

class Bob;

class Spider : public Enemy {
 private:
  int dir;
  bool isVert;
 public:
  Spider(Level* l, float x, float y, bool d);

  virtual void act();
  virtual int getSpeed() { return 2; }
};

#endif
