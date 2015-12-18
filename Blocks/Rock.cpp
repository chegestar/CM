#include "Rock.h"
#include <Level.h>
#include <utilities.h>
#include <Bob.h>
#include <Pit.h>

Rock::Rock(Level* l,float x_,float y_) : 
  Actor(l,x_,y_,l->getWidth(),l->getHeight()), Block(l,x_,y_), Mover(l,x_,y_,width,height){

  static_cast<sf::RectangleShape*>(shape)->setFillColor(sf::Color(150,150,30));

}

void Rock::act() {

  std::vector<Actor*> hits;
  level->testHitStationary(this,hits);
  for (unsigned int i=0;i<hits.size();i++) {
    Actor* actor = hits[i];
    if (actor==this) continue;

    if (dynamic_cast<Block*>(hits[i])) {
      int dir = getApproachDir(this,actor);
      if (dir==0&&getLastX1()!=actor->getX2()&&getLastX2()!=actor->getX1()) 
        setPosition(getX1(),actor->getY2());
      else if (dir==1)
        setPosition(actor->getX1()-width,getY1());
      else if (dir==2&&getLastX1()!=actor->getX2()&&getLastX2()!=actor->getX1())
        setPosition(getX1(),actor->getY1()-height);
      else if (dir==3)
        setPosition(actor->getX2(),getY1());
    }
    else if (dynamic_cast<Pit*>(hits[i])) {
      if (!getDead()) {
        hits[i]->setDead();
        setDead();
      }
    }
  }
  Bob* b =level->getBob();
  if (isRectangularHit(this,b)) {
    int dir = getApproachDir(b,this);

    if (dir==0)
      b->setPosition(b->getX1(),getY2());
    else if (dir==1)
      b->setPosition(getX1()-b->getWidth(),b->getY1());
    else if (dir==2)
      b->setPosition(b->getX1(),getY1()-b->getHeight());
    else if (dir==3)
      b->setPosition(getX2(),b->getY1());
  }
  Mover::act();
}

void Rock::render(sf::RenderWindow& window) {
  static_cast<sf::RectangleShape*>(shape)->setPosition(getX1(),getY1());
  window.draw(*shape);
}
