#include "Crystal.h"
#include <utilities.h>
#include <Level.h>
#include <GemDoor.h>
#include <stdio.h>
Crystal::Crystal(Level* l, float x_, float y_, C_CODE col,std::vector<GemDoor*>* ds) : 
  Collectable(l,x_,y_,l->getWidth(),l->getHeight()) {
  c=col;
  doors = ds;
  for (unsigned int i=0;i<doors->size();i++)
    (*doors)[i]->addCrystal();

 std::vector<std::string> keys;
  char key[20];
  for (int i=0;i<32;i++) {
    sprintf(key,"%s_gem_%d",getColorString(c),i);
    keys.push_back(std::string(key));
  }
  texture_keys.push_back(keys);
}

int Crystal::activate() {
  Collectable::activate();
  for (unsigned int i=0;i<doors->size();i++)
    (*doors)[i]->removeCrystal();
  return getColorScore(c);
}

void Crystal::render(sf::RenderWindow& window) {
  Actor::render(window);
  texture_step++;
}
