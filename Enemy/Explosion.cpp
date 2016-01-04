#include "Explosion.h"
#include <Level.h>
#include <Item.h>
#include <Block.h>
#include <Enemy.h>
#include <utilities.h>

Explosion::Explosion(Level* l, float x_, float y_) :
  Actor(l,x_,y_,l->getWidth(),l->getHeight()),Die(l,x_,y_,width,height){
  shape = new sf::CircleShape();
}

bool isExplodable(Actor* actor) {
  Bob* b;
  return dynamic_cast<Block*>(actor)||dynamic_cast<Item*>(actor)||
    (b=dynamic_cast<Bob*>(actor))&&!b->isInvuln()||dynamic_cast<Enemy*>(actor);
}

void Explosion::act() {
  const float speed = 2.5;
  x-=speed/2;
  y-=speed/2;
  width+=speed;
  height+=speed;
  if (width>level->getWidth()*3-speed*2)
    setDead();
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

}

