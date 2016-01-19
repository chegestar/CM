#include <Spider.h>
#include <Light.h>

#ifndef __FIREBALL_H__
#define __FIREBALL_H__

class Fireball : public Spider {
 protected:
  Light* light;
 public:
  Fireball(Level* l, float x, float y, bool d);
  ~Fireball();

  
  virtual int getSpeed() { return 3; }

  void act();
  void render(sf::RenderWindow& window);
  void addLights(sf::RenderTexture& darkness);
};
#endif
