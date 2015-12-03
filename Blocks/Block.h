#include <SFML/Graphics.hpp>
#include <Actor.h>

#ifndef __BLOCK_H__
#define __BLOCK_H__

class Block : public Actor{
 private:

 public:
  Block(Level* l,int x,int y);
  
  void act();
  void render(sf::RenderWindow& window);

};

#endif
