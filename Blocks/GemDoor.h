#include <Block.h>
#include <vector>

#ifndef _GEMDOOR_H_
#define _GEMDOOR_H_

class Collectable;

class GemDoor : public Block{
 private:
  int num_gems;

 public:
  GemDoor(Level* l,int x,int y);

  void addCrystal() {num_gems++;}
  void removeCrystal() {num_gems--; if (num_gems<=0) isDead=true;}

  void act();
  void render(sf::RenderWindow& window);

};

#endif
