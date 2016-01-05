#include <Switch.h>

#ifndef __LIGHT__H__
#define __LIGHT__H__

class Light : public Switch {
 protected:
  sf::CircleShape light;
 public:
  Light(Level* l, float x_, float y_,float radius);

  virtual int activate();

  void render(sf::RenderWindow&);
};

#endif
