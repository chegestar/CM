#include "Fireball.h"
#include <Level.h>
#include <utilities.h>
Fireball::Fireball(Level* l, float x, float y,bool d) :
  Actor(l,x,y,32*4.0/5,32*4.0/5), Spider(l,x,y,d) {
  texture_keys.clear();

  light=NULL;
  if (l->getZone()==ICE||l->getZone()==DARK) {

    float rad = l->getWidth()*3/2;
    light = new Light(level,x,y,rad);

  }
  char key[20];
  std::vector<std::string> keys;
  for (int i=0;i<8;i++) {
    sprintf(key,"fireball_right_%d",i);
    keys.push_back(key);
  }
  texture_keys.push_back(keys);
  keys.clear();
  for (int i=0;i<8;i++) {
    sprintf(key,"fireball_up_%d",i);
    keys.push_back(key);
  }
  texture_keys.push_back(keys);
  keys.clear();
  for (int i=0;i<8;i++) {
    sprintf(key,"fireball_left_%d",i);
    keys.push_back(key);
  }
  texture_keys.push_back(keys);
  keys.clear();
  for (int i=0;i<8;i++) {
    sprintf(key,"fireball_down_%d",i);
    keys.push_back(key);
  }
  texture_keys.push_back(keys);
  
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

void Fireball::addLights(sf::RenderTexture& darkness) {
  light->addLights(darkness);
}
