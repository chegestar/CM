#include <Enemy.h>

#ifndef __BOSS_H__
#define __BOSS_H__

class Boss : public Enemy {
 protected:
  int hp;
  int bob_lives;
 public:
  Boss(Level* l, float x_, float y_, float w, float h);

  virtual void reset() {}
  virtual void act();


};

#endif
