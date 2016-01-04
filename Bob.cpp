#include "Bob.h"
#include <Rock.h>
#include <Level.h>
#include <Exit.h>
#include <utilities.h>
#include <Collectable.h>
#include <FireBoot.h>
#include <Dynamite.h>

#include <cassert>

Bob::Bob(Level* l,float x_,float y_) : 
  Actor(l,x_,y_,l->getWidth()*5/8,l->getHeight()*5/8), 
  Mover(l,x,y,width,height),
  startx(x), starty(y){
  isExit=false;
  num_lives=3;
  score=0;
  specials=0;
  hp=100;
  has_item = new unsigned int[MAX_INVENTORY];
  for (unsigned int i=0;i<MAX_INVENTORY;i++)
    has_item[i]=0;
  has_dropped=false;


  texture_keys.push_back("bob_up");
  texture_keys.push_back("bob_left");
  texture_keys.push_back("bob_down");
  texture_keys.push_back("bob_right");

}

Bob::~Bob() {
  delete [] has_item;
}

void Bob::web() {
  if (!isWeb) {
    shiftX(-(getX1()-getLastX1())*3.5/5);
    shiftY(-(getY1()-getLastY1())*3.5/5);
  }
  isWeb=true;
}

void Bob::drain() {
  if (!isDrain) {
    hp-=.25;
  }
  if (hp<=0)
    die();
  isDrain=true;
}
void Bob::act() {
  Mover::act();
  isWeb=false;
  if (!isDrain) hp+=1;
  if (hp>100)
    hp=100;
  isDrain=false;

  float speed = 2.5;
  if (has_item[FIRE_BOOT]) {
    speed*=3.5/5;
  }
  bool didMove=false;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    didMove=true;
    texture_set=0;
    y-=getMovementCorrectionY(speed);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    didMove=true;
    texture_set=2;
    y+=getMovementCorrectionY(speed);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    didMove=true;
    texture_set=3;
    x-=getMovementCorrectionX(speed);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    didMove=true;
    texture_set=1;
    x+=getMovementCorrectionX(speed);
  }
  if (didMove) {
    texture_step++;
  }
  else
    texture_step=0;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    if (!has_dropped) {
      int r = y/level->getHeight();
      int c = x/level->getWidth();
      Item* item = popInventory();
      if (item) {
        level->findOpenPosition(r,c);
        item->setPosition(c*level->getWidth(),r*level->getHeight());
        level->addStationary(item,r,c,false);
        recent_drops.insert(item);
        has_dropped=true;
      }
    }

  }
  else {
    has_dropped=false;
  }
    
  std::set<Item*> new_drops;
  std::vector<Actor*> stationary;
  level->testHitStationary(this,stationary);
  for (unsigned int i=0;i<stationary.size();i++) {
    Actor* actor = stationary[i];
    if (!actor) continue;
    int dir = getApproachDir(this,actor);
    if (dynamic_cast<Rock*>(actor)) {
      if (dir%2) 
        actor->shiftY(getY1()-actor->getY2());
      if ((dir>>1)%2)
        actor->shiftX(getX2()-actor->getX1());
      if ((dir>>2)%2)
        actor->shiftY(getY2()-actor->getY1());
      if ((dir>>3)%2)
        actor->shiftX(getX1()-actor->getX2());
    }
    else if (dynamic_cast<Block*>(actor)) {
      int dir = getApproachDir(this,actor);
      Block* b = dynamic_cast<Block*>(actor);
      b->push_back(this,dir);
    }
    else if (dynamic_cast<Item*>(actor)) {
      Item* item = static_cast<Item*>(actor);
      if (recent_drops.find(item)!=recent_drops.end()) {
        new_drops.insert(item);
      }
      else  {
        if (pushInventory(item)) {
          
          actor->removePosition();
        }
      }
    }
    else if (dynamic_cast<Collectable*>(actor)) {
      int s =actor->activate();
      score+=s;
    }
    else if (dynamic_cast<Switch*>(actor)) {
      actor->activate();
    }
  }
  recent_drops=new_drops;

  std::vector<Collectable*> collects;
  level->testHitCollectable(this,collects);
  
  for (unsigned int i=0;i<collects.size();i++) {
    Collectable* collect = collects[i];
    if (!collect) continue;
    int s = collect->activate();
    score+=s;
  }


}


I_CODE Bob::convertItemToIndex(Item* item) {
  if (dynamic_cast<FireBoot*>(item)) 
    return FIRE_BOOT;
  else if (dynamic_cast<Dynamite*>(item))
    return DYNAMITE;
  else
    return NO_ITEM;
}

bool Bob::pushInventory(Item* item) {

  I_CODE index = convertItemToIndex(item);
  assert(index!=NO_ITEM);
  inventory.push_back(item);
  has_item[index]++;
  return true;
}

Item* Bob::popInventory() {
  if (inventory.size()==0)
    return NULL;
  Item* item = *(inventory.begin());
  I_CODE index = convertItemToIndex(item);
  assert(index!=NO_ITEM);
  inventory.pop_front();
  has_item[index]--;
  return item;
}

bool Bob::hasItem(I_CODE index) {
  assert(index!=NO_ITEM);
  assert(index<MAX_INVENTORY);
  return has_item[index];
}

void Bob::removeDynamite(C_CODE color) {
  std::list<Item*>::iterator itr;
  for (itr=inventory.begin();itr!=inventory.end();itr++) {
    Dynamite* d;
    if ((d=dynamic_cast<Dynamite*>(*itr))) {
      if (d->getColor()==color)  {
        std::list<Item*>::iterator temp = itr;
        itr--;
        inventory.erase(temp);
      }
    }
  }
}
