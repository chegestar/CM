#include "Fireball.h"
#include <Level.h>
#include <utilities.h>
Fireball::Fireball(Level* l, float x, float y,bool d) :
  Actor(l,x,y,32*4.0/5,32*4.0/5), Spider(l,x,y,d) {
  texture_keys.clear();

  light=NULL;
  if (l->getZone()==ICE) {

    float rad = l->getWidth()*3/2;
    light = new Light(level,x,y,rad);

  }

  texture_keys.push_back("fireball_right");
  texture_keys.push_back("fireball_up");
  texture_keys.push_back("fireball_left");
  texture_keys.push_back("fireball_down");
  
}
Fireball::~Fireball() {
  if (light) delete light;
}

void Fireball::act() {
  Spider::act();

  if (light) {
    light->setPosition(x-width*1.375,y-height*1.375);
    if (isRectangularHit(level->getBob(),light)) {
      light->activate();
    }
  }
}

void Fireball::render(sf::RenderWindow& window) {
  if (level->getZone()==ICE) {
    light->render(window);
  }
  texture_set=1+isVert-dir;
  Actor::render(window);
}
