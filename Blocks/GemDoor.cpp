#include "GemDoor.h"
#include <Level.h>
#include <utilities.h>
GemDoor::GemDoor(Level* l,int x,int y,C_CODE col) : Actor(l,x,y,l->getWidth(),l->getHeight()), Block(l,x,y) {
  num_gems=0;
  c=col;
  us = NULL;

  char key[15];
  sprintf(key,"%s_gate",getColorString(c));
  texture_keys.clear();
  texture_keys.push_back(std::string(key));

}


void GemDoor::render(sf::RenderWindow& window) {
  texture_set=0;
  Block::render(window);
}

std::list<Rock*>::iterator* GemDoor::removePosition() {
  if (us) delete us;
  return Block::removePosition();

}
