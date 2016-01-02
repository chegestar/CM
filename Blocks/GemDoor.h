#include <Block.h>
#include <Codes.h>

#ifndef _GEMDOOR_H_
#define _GEMDOOR_H_

class GemDoor : public Block{
 private:
  int num_gems;
  C_CODE c;
 public:
  GemDoor(Level* l,int x,int y,C_CODE col);

  void addCrystal() {num_gems++;}
  void removeCrystal() {num_gems--; if (num_gems<=0) setDead();}

  void render(sf::RenderWindow& window);

};

#endif
