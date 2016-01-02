#include "Explosion.h"
#include <Level.h>
#include <Crystal.h>
#include <utilities.h>

Explosion::Explosion(Level* l, float x_, float y_) :
  Actor(l,x_,y_,l->getWidth(),l->getHeight()),Enemy(l,x_,y_,width,height){
  
}

bool isExplodable(Actor* actor) {
  return (!dynamic_cast<Explosion*>(actor)&&!dynamic_cast<Crystal*>(actor));
}

void Explosion::act() {
  const float speed = 2.5;
  x-=speed/2;
  y-=speed/2;
  width+=speed;
  height+=speed;
  if (width>level->getWidth()*3-speed*2)
    setDead();
  Enemy::act();
  Level::ACTORS::iterator itr=level->beginActor();
  do {
    if (isExplodable(itr->second)&&isRectangularHit(this,itr->second))
      itr->second->setDead();
  }
  while (level->iterateActor(itr)!=level->endActor());
}

void Explosion::render(sf::RenderWindow& window) {
  static_cast<sf::CircleShape*>(shape)->setRadius(width/2);
  Die::render(window);
}

