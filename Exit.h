
#include "CheckPoint.h"

#ifndef __EXIT__H__
#define __EXIT__H__

class Exit : public CheckPoint {
 public:
  Exit(Level* l, float x_,float y_);

  void render(sf::RenderWindow& window);

 
};

#endif
