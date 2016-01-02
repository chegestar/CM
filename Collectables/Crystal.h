#include <Collectable.h>
#include <Codes.h>
#ifndef __CRYSTAL__H__
#define __CRYSTAL__H__

class GemDoor;


class Crystal : public Collectable {
 public:
  Crystal(Level* l, float x_, float y_, C_CODE col);

  void addDoor(GemDoor* d) {doors.push_back(d);}

  virtual int activate();

  void render(sf::RenderWindow& window);

 protected:
  std::vector<GemDoor*> doors;
  C_CODE c;
};

#endif
