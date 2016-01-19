#include <Die.h>
#include <Light.h>
#ifndef __LAVA__H__
#define __LAVA__H__

class Bob;

class Lava : public Die {
 private:
  bool isPath;
  Light* light;
 public:
  Lava(Level* l, float x, float y);
  ~Lava();
  bool hitBob(Bob* b);

  void setPath() {isPath=true;}

  void act();
  void render(sf::RenderWindow& window);
  void addLights(sf::RenderTexture& darkness);
};

#endif
