#include "EpCrystal.h"
#include <utilities.h>
#include <Level.h>
#include <Bob.h>

EpCrystal::EpCrystal(Level* l, float x_, float y_) : 
  Collectable(l,x_,y_,l->getWidth(),l->getHeight()) {
  std::vector<std::string> keys;
  int i=0;
  for (C_CODE col=RED;i<32;getNextColor(col)) {
    if (col==COIN)
      col=RED;
    char key[15];
    sprintf(key,"%s_gem_%d",getColorString(col),i);
    keys.push_back(key);
    i++;
  }
  texture_keys.clear();
  texture_keys.push_back(keys);
}

int EpCrystal::activate() {
  Collectable::activate();
  level->getBob()->earnEP();
  return 1000;
}


void EpCrystal::render(sf::RenderWindow& window) {
  Actor::render(window);
  texture_step++;
}
