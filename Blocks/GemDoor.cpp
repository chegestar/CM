#include "GemDoor.h"
#include <Level.h>
#include <utilities.h>
GemDoor::GemDoor(Level* l,int x,int y,C_CODE col) : Actor(l,x,y,l->getWidth(),l->getHeight()), Block(l,x,y) {
  num_gems=0;
  c=col;
  us = NULL;
  
  char key[15];
  std::vector<std::string> keys;
  if (col==COIN||col==YELLOW||col==WHITE) {
    for (int i=0;i<32;i++) {
      sprintf(key,"%s_gate_%d",getColorString(c),i);
      keys.push_back(key);
    }
  }
  else {
    sprintf(key,"%s_gate",getColorString(c));
    keys.push_back(key);
  }
  texture_keys.clear();
  texture_keys.push_back(keys);

}


void GemDoor::render(sf::RenderWindow& window) {
  texture_set=0;
  Block::render(window);
}

std::list<Rock*>::iterator* GemDoor::removePosition() {
  if (us) delete us;
  return Block::removePosition();

}
