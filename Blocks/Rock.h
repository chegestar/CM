#include <Mover.h>
#include <Block.h>
#ifndef __ROCK_H__
#define __ROCK_H__

class Rock : public Block, public Mover{
 private:

 public:
  Rock(Level* l,float x_,float y_);
  
  void act();
  void render(sf::RenderWindow& window);

};

#endif
