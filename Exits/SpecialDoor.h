#include <Exit.h>

#ifndef __SPECIALEXIT__H__
#define __SPECIALEXIT__H__

class SpecialDoor : public Exit {
 public:
  SpecialDoor(Level* l, float x_,float y_);
  int activate() {texture_set=0;level->getBob()->setSpecialExit();return 0;}

  void render(sf::RenderWindow& window) {Exit::render(window); texture_step++;}
 
};

#endif
