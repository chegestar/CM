#include <Collectable.h>
#include <Codes.h>
#ifndef __CRYSTAL__H__
#define __CRYSTAL__H__

class GemDoor;


class Crystal : public Collectable {
 public:
  Crystal(Level* l, float x_, float y_, C_CODE col, std::vector<GemDoor*>* ds);

  virtual int activate();

  void render(sf::RenderWindow& window);

 protected:
  std::vector<GemDoor*>* doors;
  C_CODE c;

};

#endif
