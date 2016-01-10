#include <Collectable.h>

#ifndef __HOURGLASS__H__
#define __HOURGLASS__H__

class HourGlass : public Collectable {
 private:
  bool isRed;
 public:
  HourGlass(Level* l, float x_, float y_,bool isR);

  virtual int activate();

  void render(sf::RenderWindow& window);
};

#endif
