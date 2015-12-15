#include <Collectable.h>

#ifndef __EPCRYSTAL__H__
#define __EPCRYSTAL__H__

class EpCrystal : public Collectable {
 public:
  EpCrystal(Level* l, float x_, float y_);

  virtual int activate();

  void render(sf::RenderWindow& window);

};

#endif
