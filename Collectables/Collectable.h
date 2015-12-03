#include <Actor.h>

#ifndef __COLLECTABLE__H__
#define __COLLECTABLE__H__

class GemDoor;


class Collectable : public Actor {
 public:
  Collectable(Level* l, float x_, float y_, float w, float h);

  void addDoor(GemDoor* d) {doors.push_back(d);}

  virtual void activate();

  void act();
  void render(sf::RenderWindow& window);

 protected:
  std::vector<GemDoor*> doors;
};

#endif
