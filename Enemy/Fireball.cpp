#include "Fireball.h"
#include <Level.h>

Fireball::Fireball(Level* l, float x, float y,bool d) :
  Actor(l,x,y,32*4.0/5,32*4.0/5), Spider(l,x,y,d) {
  texture_keys.clear();

  texture_keys.push_back("fireball_right");
  texture_keys.push_back("fireball_up");
  texture_keys.push_back("fireball_left");
  texture_keys.push_back("fireball_down");
  
}


void Fireball::render(sf::RenderWindow& window) {
  texture_set=1+isVert-dir;
  Actor::render(window);
  texture_step++;
}
