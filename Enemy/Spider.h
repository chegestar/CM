#include <Enemy.h>

#ifndef __SPIDER__H__
#define __SPIDER__H__

class Bob;

class Spider : public Enemy {
 protected:
  int dir;
  bool isVert;
 public:
  Spider(Level* l, float x, float y, bool d,int di=0);

  float getBoundY1() const {return getY1()+height/4;}
  float getBoundY2() const {return getY2()-height/4;}
  virtual int getSpeed() { return 2; }
  std::vector<Line> getLines() const;
  
  void flip(bool isR) {isVert=isR;  texture_set=isVert;}

  virtual void act();
  virtual void render(sf::RenderWindow& window);
};

#endif
