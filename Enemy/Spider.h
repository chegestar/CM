#include <Enemy.h>

#ifndef __SPIDER__H__
#define __SPIDER__H__

class Bob;

class Spider : public Enemy {
 protected:
  int dir;
  bool isVert;
 public:
  Spider(Level* l, float x, float y, bool d);

  virtual int getSpeed() { return 2; }
  
  void flip(bool isR) {isVert=isR;  texture_set=isVert;}

  virtual void act();
  virtual void render(sf::RenderWindow& window);
};

#endif
