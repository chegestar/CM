#include <SFML/Graphics.hpp>
#include <Actor.h>
#include <Mover.h>

#ifndef __BOB__H__
#define __BOB__H__
class Bob : public Mover{
 private:
  int startx,starty;
 public:
  Bob(Level* l,int x_,int y_);
  
  void die() {x=startx; y = starty;}

  void act();
  void render(sf::RenderWindow& window);
};

#endif
