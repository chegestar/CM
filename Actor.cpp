#include "Actor.h"
#include <Level.h>
#include <utilities.h>

Actor::Actor(Level* l, float x_,float y_,float w,float h) {
  level = l;
  x = x_+(level->getWidth()-w)/2;
  y = y_+(level->getHeight()-h)/2;
  width = w;
  height = h;
  isDead=false;
  pointer_to_location=NULL;
  pointer_to_gem=NULL;
  pointer_to_rock=NULL;

  shape=NULL;
  texture_set=texture_step=0;
  
}

Actor::~Actor() {
  if (shape) delete shape;
  pointer_to_location=NULL;
  pointer_to_gem=NULL;
  shape=NULL;
}

float Actor::getX1() const {return x-level->getX();}
float Actor::getX2() const {return getX1()+width;}
float Actor::getY1() const {return y-level->getY();}
float Actor::getY2() const {return getY1()+height;}

void Actor::setPosition(float x_, float y_,bool keepLast) {
  x=x_+level->getX();
  y=y_+level->getY();
}

bool Actor::removePosition(std::list<Rock*>::iterator*& itr) {
  if (pointer_to_location) *pointer_to_location=NULL;
  if (pointer_to_gem) *pointer_to_gem=NULL;
  itr = pointer_to_rock;
  return true;
}

void Actor::render(sf::RenderWindow& window) {
  sf::Texture text = getGraphic(texture_keys[texture_set]);
  sprite.setTexture(text);

  int step=texture_step/3;
  float w = sprite.getLocalBounds().width;
  step %= int(round(w/32));
  sprite.setTextureRect(sf::IntRect(32*step,0,32,32));
  sprite.setPosition(getX1(),getY1());
  sprite.setScale(width/32,height/32);
  window.draw(sprite);
  sprite.setTextureRect(sf::IntRect(0,0,w,32));
}
