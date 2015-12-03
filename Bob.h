#include <SFML/Graphics.hpp>
#include <Actor.h>
#include <Mover.h>

#ifndef __BOB__H__
#define __BOB__H__
class Bob : public Mover{
 private:
  int startx,starty;
 public:
 Bob(Level* l,int x_,int y_) : Actor(l,x_+5,y_+5,20,20), Mover(l,x,y,width,height),
    startx(x), starty(y){}
  
  void die() {x=startx; y = starty;}

  void act();
  void render(sf::RenderWindow& window);
};

#endif
