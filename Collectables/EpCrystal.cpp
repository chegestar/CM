#include "EpCrystal.h"
#include <utilities.h>
#include <Level.h>
#include <Bob.h>

EpCrystal::EpCrystal(Level* l, float x_, float y_) : 
  Collectable(l,x_,y_,l->getWidth(),l->getHeight()) {
  texture_keys.push_back("Ep_gem");
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
