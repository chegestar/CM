#include "EpDoor.h"
#include <Level.h>
#include <utilities.h>

EpDoor::EpDoor(Level* l,int x,int y,int tot_levels) : Actor(l,x,y,l->getWidth(),l->getHeight()), GemDoor(l,x,y,COIN) {
  num_gems=tot_levels;

  texture_keys.clear();
  std::vector<std::string> keys;
  for (C_CODE col=RED;col<COIN;getNextColor(col)) {
    char key[15];
    sprintf(key,"%s_gate",getColorString(col));
    std::cout<<key<<"\n";
    keys.push_back(key);
  }
  texture_keys.clear();
  texture_keys.push_back(keys);

}

void EpDoor::act() {
  GemDoor::act();
  texture_step++;
  if (level->getBob()->getSpecials()==num_gems)
    setDead();
}

void EpDoor::render(sf::RenderWindow& window) {
  GemDoor::render(window);
}
