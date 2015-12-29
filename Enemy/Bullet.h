#include <Enemy.h>


#ifndef __BULLET__H__
#define __BULLET__H__


class Bullet : public Enemy {
 private:
  float angle,v;

 public:
  Bullet(Level* l, float x, float y, float w, float h, float ang, float vel);

  void setAngle(float ang) {angle=ang;}
  virtual void act();
};

#endif
