
#include <Actor.h>
#include <Mover.h>

#ifndef __BOB__H__
#define __BOB__H__
class Bob : public Mover{
 private:
  float startx,starty;
 public:
  Bob(Level* l,float x_,float y_);
  
  void die() {x=startx; y = starty;}

  void act();
  void render(sf::RenderWindow& window);
};

#endif
