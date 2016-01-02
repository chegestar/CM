#include "Rock.h"
#include <Level.h>
#include <utilities.h>
#include <Bob.h>
#include <Pit.h>

Rock::Rock(Level* l,float x_,float y_) : 
  Actor(l,x_,y_,l->getWidth()*3.5/5,l->getHeight()*3.5/5), Block(l,x_,y_), Mover(l,x_,y_,width,height){

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
      Block* b = dynamic_cast<Block*>(actor);
      b->push_back(this,dir);

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
    push_back(b,dir);
  }
  Mover::act();
}

void Rock::render(sf::RenderWindow& window) {
  static_cast<sf::RectangleShape*>(shape)->setPosition(getX1(),getY1());
  window.draw(*shape);
}
