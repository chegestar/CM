#include "Explosion.h"
#include <Level.h>
#include <Item.h>
#include <EpDoor.h>
#include <Enemy.h>
#include <utilities.h>

Explosion::Explosion(Level* l, float x_, float y_) :
  Actor(l,x_,y_,l->getWidth(),l->getHeight()),Die(l,x_,y_,width,height){
  shape = new sf::CircleShape();
  char key[20];
  std::vector<std::string> keys;
  for (int i=0;i<7;i++) {
    sprintf(key,"explosion_%d",i);
    keys.push_back(key);
  }
  texture_keys.push_back(keys);

}

bool isExplodable(Actor* actor) {
  Bob* b;
  return (dynamic_cast<Block*>(actor)&&!dynamic_cast<EpDoor*>(actor))||dynamic_cast<Item*>(actor)||
    ((b=dynamic_cast<Bob*>(actor))&&!b->isInvuln())||dynamic_cast<Enemy*>(actor);
}

void Explosion::act() {
  const float speed = 2.5;
  x-=speed/2;
  y-=speed/2;
  width+=speed;
  height+=speed;
  float max_width=level->getWidth()*3-speed*2;
  if (width>max_width)
    setDead();
  else {
    texture_step = (int)(7*width/max_width)*3;
  }
  Die::act();
  Level::ACTORS::iterator itr=level->beginActor();
  do {
    if (isExplodable(itr->second)&&isRectangularHit(this,itr->second))
      itr->second->setDead();
  }
  while (level->iterateActor(itr)!=level->endActor());
}

void Explosion::render(sf::RenderWindow& window) {
  static_cast<sf::CircleShape*>(shape)->setRadius(width/2);
  static_cast<sf::CircleShape*>(shape)->setPosition(getX1(),getY1());
  window.draw(*shape);
  Actor::render(window);
}

