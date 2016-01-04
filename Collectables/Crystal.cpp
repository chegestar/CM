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

  char key[15];
  sprintf(key,"%s_gem",getColorString(c));
  texture_keys.push_back(std::string(key));
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
