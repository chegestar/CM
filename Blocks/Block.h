#include <Actor.h>

#ifndef __BLOCK_H__
#define __BLOCK_H__

class Block : virtual public Actor{
 private:
  bool isL,isR,isU,isD;
 public:
  Block(Level* l,float x_,float y_);
  
  void push_back(Actor* actor,int dir);
  void setDirs(bool u,bool r, bool d, bool l);

  void render(sf::RenderWindow& window);

};

#endif
