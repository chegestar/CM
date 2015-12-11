#include <Actor.h>

#ifndef __BLOCK_H__
#define __BLOCK_H__

class Block : public Actor{
 private:

 public:
  Block(Level* l,float x_,float y_);
  
  void act();
  void render(sf::RenderWindow& window);

};

#endif
