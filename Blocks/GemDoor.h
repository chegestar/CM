#include <Block.h>
#include <Codes.h>

#ifndef _GEMDOOR_H_
#define _GEMDOOR_H_

class GemDoor : public Block{
 private:
  int num_gems;
  C_CODE c;
  std::vector<GemDoor*>* us;
 public:
  GemDoor(Level* l,int x,int y,C_CODE col);

  void own(std::vector<GemDoor*>* u) {us=u;}
  void addCrystal() {num_gems++;}
  void removeCrystal() {num_gems--; if (num_gems<=0) setDead();}
  
  std::list<Rock*>::iterator* removePosition();

  void render(sf::RenderWindow& window);

};

#endif
