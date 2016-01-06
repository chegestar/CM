#include "EpDoor.h"
#include <Level.h>
#include <utilities.h>

EpDoor::EpDoor(Level* l,int x,int y,int tot_levels) : Actor(l,x,y,l->getWidth(),l->getHeight()), GemDoor(l,x,y,COIN) {
  num_gems=tot_levels;

  texture_keys.clear();
  texture_keys.push_back("Ep_gate");

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
