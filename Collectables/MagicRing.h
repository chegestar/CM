#include <Collectable.h>

#ifndef __MAGICRING__H__
#define __MAGICRING__H__

class MagicRing : public Collectable {
 public:
  MagicRing(Level* l, float x_, float y_);

  virtual int activate();

  void render(sf::RenderWindow& window);

};

#endif
