#include "Bob.h"
#include <Rock.h>
#include <Level.h>
#include <Exit.h>
#include <utilities.h>
#include <Collectable.h>
#include <FireBoot.h>

#include <cassert>

Bob::Bob(Level* l,float x_,float y_) : 
  Actor(l,x_,y_,l->getWidth()*2/3,l->getHeight()*2/3), 
  Mover(l,x,y,width,height),
  startx(x), starty(y){
  isExit=false;
  num_lives=3;
  score=0;
  specials=0;

  has_item = new bool[MAX_INVENTORY];
  for (unsigned int i=0;i<MAX_INVENTORY;i++)
    has_item[i]=false;

  shape = new sf::RectangleShape(sf::Vector2f(width,height));
  static_cast<sf::RectangleShape*>(shape)->setFillColor(sf::Color(255,255,0));

}

Bob::~Bob() {
  delete [] has_item;
}

void Bob::web() {
  if (!isWeb) {
    shiftX(-(getX1()-getLastX1())*3.0/5);
    shiftY(-(getY1()-getLastY1())*3.0/5);
  }
  isWeb=true;
}

void Bob::act() {
  Mover::act();
  
  isWeb=false;

  float speed = 3;
  if (has_item[FIRE_BOOT]) {
    speed*=3.5/5;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    y-=getMovementCorrectionY(speed);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    y+=getMovementCorrectionY(speed);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    x-=getMovementCorrectionX(speed);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    x+=getMovementCorrectionX(speed);

  std::vector<Actor*> stationary;
  level->testHitStationary(this,stationary);
  for (unsigned int i=0;i<stationary.size();i++) {
    Actor* actor = stationary[i];
    if (!actor) continue;
    int dir = getApproachDir(this,actor);
    if (dynamic_cast<Rock*>(actor)) {
      if (dir==0) 
        actor->shiftY(getY1()-actor->getY2());
      else if (dir==1)
        actor->shiftX(getX2()-actor->getX1());
      else if (dir==2)
        actor->shiftY(getY2()-actor->getY1());
      else if (dir==3)
        actor->shiftX(getX1()-actor->getX2());
    }
    else if (dynamic_cast<Block*>(actor)) {
      int dir = getApproachDir(this,actor);
      if (dir==0&&getLastX1()!=actor->getX2()&&getLastX2()!=actor->getX1()) {
        setPosition(getX1(),actor->getY2());
      }
      else if (dir==1)
        setPosition(actor->getX1()-width,getY1());
      else if (dir==2&&getLastX1()!=actor->getX2()&&getLastX2()!=actor->getX1())
        setPosition(getX1(),actor->getY1()-height);
      else if (dir==3)
        setPosition(actor->getX2(),getY1());
    }
    else if (dynamic_cast<Item*>(actor)) {
      if (pushInventory(static_cast<Collectable*>(actor))) {
        actor->setDead();
      }
    }
    else if (dynamic_cast<Collectable*>(actor)) {
      int s =actor->activate();
      score+=s;
    }
    else if (dynamic_cast<Switch*>(actor)) {
      actor->activate();
    }
    else if (dynamic_cast<Exit*>(actor)) {
      isExit=true;
    }
    else if (dynamic_cast<CheckPoint*>(actor)) {
      startx = actor->getX1()+level->getX();
      starty = actor->getY1()+level->getY();
    }
  }

  std::vector<Collectable*> collects;
  level->testHitCollectable(this,collects);
  
  for (unsigned int i=0;i<collects.size();i++) {
    Collectable* collect = collects[i];
    if (!collect) continue;
    int s = collect->activate();
    score+=s;
  }


}

void Bob::render(sf::RenderWindow& window) {
  static_cast<sf::RectangleShape*>(shape)->setPosition(getX1(),getY1());
  window.draw(*shape);
}

I_CODE Bob::convertCollectableToIndex(Collectable* item) {
  if (dynamic_cast<FireBoot*>(item)) 
    return FIRE_BOOT;
  else
    return NO_ITEM;
}

bool Bob::pushInventory(Collectable* item) {

  I_CODE index = convertCollectableToIndex(item);
  if (hasItem(index)) {return false;} 
  assert(index!=NO_ITEM);
  inventory.push(item);
  has_item[index] = true;
  return true;
}

Collectable* Bob::popInventory() {
  Collectable* item = inventory.front();
  I_CODE index = convertCollectableToIndex(item);
  assert(index!=NO_ITEM);
  inventory.pop();
  has_item[index]=false;
  return item;
}

bool Bob::hasItem(I_CODE index) {
  assert(index!=NO_ITEM);
  assert(index<MAX_INVENTORY);
  return has_item[index];
}
