#include <Collectable.h>

#ifndef __COIN__H__
#define __COIN__H__

class Coin : public Collectable {
 public:
  Coin(Level* l, float x_, float y_);

  std::vector<Circle> getCircles() const;

  virtual int activate();

  void render(sf::RenderWindow& window);

};

#endif
