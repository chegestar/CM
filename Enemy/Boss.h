#include <Enemy.h>

#ifndef __BOSS_H__
#define __BOSS_H__

class Boss : public Enemy {
 protected:
  int hp;
  
 public:
  Boss(Level* l, float x_, float y_, float w, float h);

  virtual void act();

  //void render(sf::RenderWindow& window);
};

#endif
